module Collider.RectCollider;
import MyLib.Math.Vector2;

using namespace math;

namespace col2d
{
    RectCollider::RectCollider(ColliderDef* def, const Vector2f& size)
        :Collider(def)
        , m_baseRect()
        , m_sweptRect()
    {
        // ビジターの初期化
        m_visitor = std::make_unique<RectColliderVisitor>(*this);

        // 矩形の初期化
        m_baseRect.pos = m_colDef->localPos;
        m_baseRect.size = size;

        // スイープ矩形の初期化
        m_sweptRect.pos = m_colDef->localPos;
        m_sweptRect.size = m_baseRect.size;
    }

    bool RectCollider::IsColliding(const Vector2f& point)
    {
        // スイープ矩形を使用して衝突判定
        if (m_colDef->shouldCCD)
        {
            CalcSweptRect(m_velocity);
            return (point.x >= m_sweptRect.Left() &&
                point.x <= m_sweptRect.Right() &&
                point.y >= m_sweptRect.Top() &&
                point.y <= m_sweptRect.Bottom());
        }

        //通常の衝突判定
        return (point.x >= m_baseRect.Left() &&
            point.x <= m_baseRect.Right() &&
            point.y >= m_baseRect.Top() &&
            point.y <= m_baseRect.Bottom());
    }


    bool RectCollider::IsColliding(const RectCollider& other)
    {
        // 連続衝突検出を行う場合
        if (m_colDef->shouldCCD || other.GetColliderDef()->shouldCCD)
        {
            // 相対速度の算出
            const math::Vector2f v_rel{
                m_velocity.x - other.GetVelocity().x,
                m_velocity.y - other.GetVelocity().y
            };

            // スイープ矩形の算出
            CalcSweptRect(v_rel);

            return m_sweptRect.AABB(other.GetRect());
        }

        // 通常の矩形衝突判定
        return m_baseRect.AABB(other.GetRect());
    }

    void RectCollider::CalcSweptRect(Vector2f velocity)
    {
        m_sweptRect.pos.x = std::min(m_colDef->localPos.x, m_colDef->localPos.x + velocity.x);
        m_sweptRect.pos.y = std::min(m_colDef->localPos.y, m_colDef->localPos.y + velocity.y);
        m_sweptRect.size = m_baseRect.size + Vector2f(std::abs(velocity.x), std::abs(velocity.y));
    }
}
