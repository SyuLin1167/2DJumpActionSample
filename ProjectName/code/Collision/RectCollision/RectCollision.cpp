#include"RectCollision.h"
#include"MapCollision/MapCollision.h"

namespace collision
{
    RectCollision::RectCollision(Vector2<float>& _pos, Vector2<float>& _size, Vector2<float>& _velocity)
        : baseRect(shape::Rect(_pos, _size))
        , pos(_pos)
        , size(_size)
        , velocity(_velocity)
        , sweptRect()
        , diffX()
        , diffY()
    {
        sweptRect.pos = pos;
    }

    RectCollision::RectCollision(shape::Rect _rect, Vector2<float>& _velocity)
        : baseRect(_rect)
        , pos(baseRect.pos)
        , size(baseRect.size)
        , velocity(_velocity)
        , sweptRect()
        , diffX()
        , diffY()
    {
        sweptRect.pos = pos;
    }

    void RectCollision::Dispatch(uint64_t _handle, CollisionBase* _other)
    {
        _other->ColliderWith(*this, targetColInfo[_handle]);
    }

    void RectCollision::ColliderWith(MapCollision& _other, TargetColInfo& _info)
    {
        _other.HandlingCollision(*this, _info);
    }

    void RectCollision::ColliderWith(RectCollision& _other, TargetColInfo& _info)
    {
        //衝突判定
        auto otherRect = _other.SweptRect();
        if (HasColliderRect(otherRect))
        {
            //非貫通なら押し戻す
            if (!_info.isTrriger)
            {
                CalcDiff(_other);
                PushBack();
            }

            //衝突イベントがあるなら実行
            if (!_info.events.empty())
            {
                for (auto& event : _info.events)
                {
                    event();
                }
            }
        }
    }
    void RectCollision::CalcDiff(const RectCollision& _other)
    {
        //X軸差分
        diffX.x = _other.pos.x - (pos.x + size.x);
        diffX.y = (_other.pos.x + _other.size.x) - pos.x;

        //Y軸差分
        diffY.x = _other.pos.y - (pos.y + size.y);
        diffY.y = (_other.pos.y + _other.size.y) - pos.y;
    }

    void RectCollision::ExclDiff(bool _xx, bool _xy, bool _yx, bool _yy)
    {
        //X軸の不要な差分を除去
        if (SignVelocity().x != 0)
        {
            if (_xx)
            {
                diffX.x = INFINITY;
            }
            if (_xy)
            {
                diffX.y = INFINITY;
            }
        }

        //Y軸の不要な差分を除去
        if (SignVelocity().y != 0)
        {
            if (_yx)
            {
                diffY.x = INFINITY;
            }
            if (_yy)
            {
                diffY.y = INFINITY;
            }
        }
    }

    void RectCollision::PushBack()
    {
        //差分に沿った軸ごとの優先順位
        float dx = (fabs(diffX.x) < fabs(diffX.y)) ? diffX.x : diffX.y;
        float dy = (fabs(diffY.x) < fabs(diffY.y)) ? diffY.x : diffY.y;

        if (fabs(dx) == fabs(dy))
        {
            return;
        }

        //最も近い方向に押し戻す
        if (fabs(dx) < fabs(dy))
        {
            pos.x += dx;
            velocity.x = 0;
        }
        else
        {
            pos.y += dy;
            if ((dy < 0 && SignVelocity().y > 0) || (dy > 0 && SignVelocity().y < 0))
            {
                velocity.y = 0;
            }
        }
    }

    void RectCollision::CalcSweptRect()
    {
        //左上座標を算出
        Vector2<float> sweptMin =
        {
            std::min<float>(pos.x, pos.x - velocity.x),
            std::min<float>(pos.y, pos.y - velocity.y)
        };
        sweptRect.pos = sweptMin;

        //右下を算出
        sweptRect.size = size + Vector2<float>(std::abs(velocity.x), std::abs(velocity.y));
    }
}