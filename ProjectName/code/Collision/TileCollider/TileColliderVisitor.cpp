module Collider.TileColliderVisitor;
import MyLib.Math.Vector2;
import Collider.TileCollider;

using namespace math;

namespace col2d
{
    TileColliderVisitor::TileColliderVisitor(TileCollider& issue)
        : m_issue(issue)
    {
        // 処理なし
    }

    void TileColliderVisitor::Visit(RectCollider& collider)
    {
        // コライダーが有効でない場合は処理を行わない
        if (!m_issue.GetColliderDef()->isActive || !collider.GetColliderDef()->isActive)
        {
            return;
        }

        // 衝突が発生したかどうか
        bool hadContact = false;

        // 移動量からサブステップ数を決める
        Vector2f vel = collider.GetVelocity();
        const float longest = std::max(std::abs(vel.x), std::abs(vel.y));
        const Vector2f tileSize = m_issue.GetTileSize();
        const float stepMax = 0.5f * std::min(tileSize.x, tileSize.y);
        int N = std::max(1, static_cast<int>(std::ceil(longest / stepMax)));
        vel /= N;

        // 仮想位置での矩形
        auto stepRect = collider.GetRect();

        // サブステップごとに衝突判定と解決を行う
        for (int i = 0; i < N; ++i)
        {
            // 仮想移動
            collider.AddVelocity(vel);
            stepRect.pos += vel;

            // 現在予定位置で衝突タイル収集
            if (m_issue.IsColliding(stepRect))
            {
                // 衝突タイルごとに処理
                auto hitTileKeys = m_issue.TakeHitTileKeys();
                while (!hitTileKeys.empty())
                {
                    // 衝突タイル情報取得
                    auto& [key, index] = hitTileKeys.front();
                    hitTileKeys.pop();
                    auto tileInfo = m_issue.GetTileInfo(key, index);

                    // タイルコライダーが存在しない場合はスキップ
                    if (!tileInfo || !tileInfo->collider)
                    {
                        continue;
                    }

                    // 現在位置で本当に衝突しているか再確認
                    if (collider.IsColliding(*tileInfo->collider))
                    {
                        m_resolver.Resolve(collider, *tileInfo);
                        hadContact = true;
                    }
                }
            }
        }

        // 衝突していればイベントを実施する
        if (hadContact)
        {
            collider.TriggerEvent(m_issue.GetFilter().category);
        }
    }
}