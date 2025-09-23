#include "RectColliderVisitor.h"
#include "RectCollider/RectCollider.h"

namespace col2d
{
    void RectColliderVisitor::Visit(col2d::RectCollider& _target)
    {
        // コライダーが有効でない場合は処理を行わない
        if (!issue.GetColliderDef()->isActive || !_target.GetColliderDef()->isActive)
        {
            return;
        }

        // 衝突しているか調べる
        if (issue.IsColliding(_target))
        {
            // 衝突している場合、トリガーでなければ解決処理を行う
            if (!issue.GetColliderDef()->isTrigger)
            {
                resolver.Resolve(issue, _target);
            }
        }
    }
};
