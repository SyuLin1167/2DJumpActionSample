module Collider.TileColliderVisitor;

import MyLib.Math.Vector2;
import Collider.TileCollider;

using namespace math;

namespace col2d
{
    void TileColliderVisitor::Visit(RectCollider& collider)
    {
        // コライダーが有効でない場合は処理を行わない
        if (!m_issue.GetColliderDef()->isActive || !collider.GetColliderDef()->isActive)
        {
            return;
        }
        bool hadContact = false;

        // 移動量からサブステップ数を決める
        Vector2f vel = collider.GetVelocity();
        float longest = std::max(std::abs(vel.x), std::abs(vel.y));
        float stepMax = m_issue.GetTileSize().Half().x;
        int N = std::max(1, static_cast<int>(std::ceil(longest / stepMax)));
        vel /= N;

        // サブステップごとに衝突判定と解決を行う
        for (int i = 0; i < N; ++i)
        {
            auto rect = collider.GetRect();
            rect.pos += vel;
            
            if (m_issue.IsColliding(rect))
            {
                ColliderDef* def = m_issue.GetColliderDef();
                auto hitTileKyes = m_issue.TakeHitTileKeys();

                while (!hitTileKyes.empty())
                {
                    auto& [key, index] = hitTileKyes.front();
                    hitTileKyes.pop();
                    auto tileInfo = m_issue.GetTileInfo(key, index);

                    if (!tileInfo || !tileInfo->collider)
                    {
                        continue;
                    }

                    if (collider.IsColliding(*tileInfo->collider))
                    {
                        m_resolver.Resolve(collider, *tileInfo->collider, tileInfo->adjacentFlag);
                        hadContact = true;
                    }
                }
            }
        }
        if (hadContact)
        {
            collider.TriggerEvent(m_issue.GetFilter().category);
        }
        collider.AddVelocity();
    }
}
