module Collider.RectColliderVisitor;

import MyLib.Math.Vector2;
import Collider.RectCollider;
import Collider.CircleCollider;

using namespace math;

namespace col2d
{
    RectColliderVisitor::RectColliderVisitor(RectCollider& issue)
        :m_issue(issue)
    {
        // 処理なし
    }

    void RectColliderVisitor::Visit(col2d::RectCollider& target)
    {
        // コライダーが有効でない場合は処理を行わない
        if (!m_issue.GetColliderDef()->isActive || !target.GetColliderDef()->isActive)
        {
            return;
        }

        bool hadContact = false;

        // サブステップ数を決定
        Vector2f vel = m_issue.GetVelocity();
        float longest = std::max(std::abs(vel.x), std::abs(vel.y));
        auto selfRect = m_issue.GetRect();
        float stepMax = std::max(0.0001f, std::min(selfRect.size.Half().x, selfRect.size.Half().y));
        int N = std::max(1, static_cast<int>(std::ceil(longest / stepMax)));
        vel /= static_cast<float>(N);

        // 仮想位置での矩形
        auto stepRect = m_issue.GetRect();

        // サブステップで仮想移動して衝突解決
        for (int i = 0; i < N; ++i)
        {
            m_issue.AddVelocity(vel);
            stepRect.pos += vel;

            // 衝突していたら解決する
            if (stepRect.AABB(target.GetRect()))
            {
                hadContact = true;

                // どちらかがトリガーなら押し戻しは行わない
                if (!m_issue.GetColliderDef()->isTrigger || !target.GetColliderDef()->isTrigger)
                {
                    m_resolver.Resolve(m_issue, target);
                }
            }
        }

        // 衝突していればイベントを実施する
        if (hadContact)
        {
            m_issue.TriggerEvent(target.GetFilter().category);
        }
    }

    void RectColliderVisitor::Visit(col2d::CircleCollider& target)
    {
        // コライダーが有効でない場合は処理を行わない
        if (!m_issue.GetColliderDef()->isActive || !target.GetColliderDef()->isActive)
        {
            return;
        }
        bool hadContact = false;
        // サブステップ数を決定
        Vector2f vel = m_issue.GetVelocity();
        float longest = std::max(std::abs(vel.x), std::abs(vel.y));
        auto selfRect = m_issue.GetRect();
        float stepMax = std::max(0.0001f, std::min(selfRect.size.Half().x, selfRect.size.Half().y));
        int N = std::max(1, static_cast<int>(std::ceil(longest / stepMax)));
        vel /= static_cast<float>(N);
        // 仮想位置での矩形
        auto stepRect = m_issue.GetRect();
        // サブステップで仮想移動して衝突解決
        for (int i = 0; i < N; ++i)
        {
            m_issue.AddVelocity(vel);
            stepRect.pos += vel;
            // 衝突していたら解決する
            if (m_issue.IsColliding(target))
            {
                hadContact = true;
                // どちらかがトリガーなら押し戻しは行わない
                if (!m_issue.GetColliderDef()->isTrigger || !target.GetColliderDef()->isTrigger)
                {
                    m_resolver.Resolve(m_issue, target);
                }
            }
        }
        // 衝突していればイベントを実施する
        if (hadContact)
        {
            m_issue.TriggerEvent(target.GetFilter().category);
        }
    }
};
