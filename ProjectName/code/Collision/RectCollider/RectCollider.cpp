#include "RectCollider.h"

namespace col2d
{
    RectCollider::RectCollider(ColliderDef* _def)
        :Collider(_def)
        , baseRect()
        , sweptRect()
    {
        visitor = std::make_unique<RectColliderVisitor>(*this);
        Initialize();
    }

    void RectCollider::Initialize(const Vector2f& _size)
    {
        // 矩形の初期化
        baseRect.pos = colDef->localPos;
        baseRect.size = _size;

        // スイープ矩形の初期化
        sweptRect.pos = colDef->localPos;
        sweptRect.size = baseRect.size;
    }

    bool RectCollider::IsColliding(const Vector2f& _point)
    {
        // スイープ矩形を使用して衝突判定
        if (colDef->shouldCCD)
        {
            CalcSweptRect();
            return (_point.x >= sweptRect.Left() &&
                _point.x <= sweptRect.Right() &&
                _point.y >= sweptRect.Top() &&
                _point.y <= sweptRect.Bottom());
        }

        //通常の衝突判定
        return (_point.x >= baseRect.Left()&&
            _point.x <= baseRect.Right() &&
            _point.y >= baseRect.Top() &&
            _point.y <= baseRect.Bottom());
    }


    bool RectCollider::IsColliding(const RectCollider& _other)
    {
        // スイープ矩形を使用して衝突判定
        if (colDef->shouldCCD)
        {
            CalcSweptRect();
            return sweptRect.AABB(_other.GetRect());
        }

        // 通常の矩形衝突判定
        return baseRect.AABB(_other.GetRect());
    }

    void RectCollider::CalcSweptRect()
    {
        sweptRect.pos.x = std::min(colDef->localPos.x, colDef->localPos.x + velocity.x);
        sweptRect.pos.y = std::min(colDef->localPos.y, colDef->localPos.y + velocity.y);
        sweptRect.size = baseRect.size + Vector2(std::abs(velocity.x), std::abs(velocity.y));
    }
}
