module Collider.RectColliderVisitor;

import Collider.RectCollider;

namespace col2d
{
    void RectColliderVisitor::Visit(col2d::RectCollider& target)
    {
        // コライダーが有効でない場合は処理を行わない
        if (!m_issue.GetColliderDef()->isActive || !target.GetColliderDef()->isActive)
        {
            return;
        }

        // 衝突しているか調べる
        if (m_issue.IsColliding(target))
        {
            // 衝突している場合、トリガーでなければ解決処理を行う
            if (!m_issue.GetColliderDef()->isTrigger)
            {
                m_resolver.Resolve(m_issue, target);
            }
        }
    }
};
