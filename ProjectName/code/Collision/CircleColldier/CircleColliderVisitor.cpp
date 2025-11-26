module Collider.CircleColliderVisitor;

import MyLib.Math.Vector2;
import Collider.CircleCollider;
import Collider.RectCollider;

using namespace math;

namespace col2d
{
    CircleColliderVisitor::CircleColliderVisitor(CircleCollider& issue)
        : m_issue(issue)
    {
        // 処理なし
    }

    void CircleColliderVisitor::Visit(RectCollider& target)
    {
        // 無効なら処理しない
        if (!m_issue.GetColliderDef()->isActive || !target.GetColliderDef()->isActive)
        {
            return;
        }

        bool hadContact = false;

        // サブステップ計算
        Vector2f vel = m_issue.GetVelocity();
        float longest = std::max(std::abs(vel.x), std::abs(vel.y));
        float stepMax = std::max(0.0001f, m_issue.GetCircle().radius * 0.5f);
        int N = std::max(1, static_cast<int>(std::ceil(longest / stepMax)));
        vel /= static_cast<float>(N);

        // 仮想位置用中心
        auto stepCircle = m_issue.GetCircle();

        for (int i = 0; i < N; ++i)
        {
            // 位置更新
            m_issue.AddVelocity(vel);
            stepCircle.center += vel;

            // 衝突検出
            if (m_issue.IsCollider(target))
            {
                hadContact = true;

                // どちらかがトリガーなら押し戻しは行わない
                if (!m_issue.GetColliderDef()->isTrigger || !target.GetColliderDef()->isTrigger)
                {
                    m_resolver.Resolve(m_issue, target);
                }
            }
        }

        if (hadContact)
        {
            m_issue.TriggerEvent(target.GetFilter().category);
        }
    }
}