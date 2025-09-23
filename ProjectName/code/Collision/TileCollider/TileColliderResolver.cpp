#include "TileColliderResolver.h"
#include "TileCollider.h"

namespace col2d
{
    void TileColliderResolver::Resolve(RectCollider& _issue, const RectCollider& _other, const  uint8_t& _adjacentFlag)
    {
        // めり込み量を計算
        Vector2f diffX{};
        diffX.x = _other.GetRect().Left() - _issue.GetRect().Right();
        diffX.y = _other.GetRect().Right() - _issue.GetRect().Left();
        Vector2f diffY{};
        diffY.x = _other.GetRect().Top() - _issue.GetRect().Bottom();
        diffY.y = _other.GetRect().Bottom() - _issue.GetRect().Top();

        // 隣接フラグがある方向は無視する
        if (_adjacentFlag & TileFlag::LEFT)
        {
            diffX.x = INFINITY;
        }
        if (_adjacentFlag & TileFlag::RIGHT)
        {
            diffX.y = INFINITY;
        }
        if (_adjacentFlag & TileFlag::TOP)
        {
            diffY.x = INFINITY;
        }
        if (_adjacentFlag & TileFlag::BOTTOM)
        {
            diffY.y = INFINITY;
        }

        float dx = (fabs(diffX.x) < fabs(diffX.y)) ? diffX.x : diffX.y;
        float dy = (fabs(diffY.x) < fabs(diffY.y)) ? diffY.x : diffY.y;


        if (fabs(dx) == fabs(dy))
        {
            return;
        }

        //最も近い方向に押し戻す
        if (fabs(dx) < fabs(dy))
        {
            // 同じ方向への押し戻しは受け付けないようにする
            if ((dx < 0 && _issue.GetVelocity().x > 0) || (dx > 0 && _issue.GetVelocity().x < 0))
            {
                _issue.AddVelocity(Vector2f(dx, 0.0f));
            }
            _issue.SetVelocity(Vector2f(0.0f, _issue.GetVelocity().y));
        }
        else
        {
            // 同じ方向への押し戻しは受け付けないようにする
            if ((dy < 0 && _issue.GetVelocity().y > 0) || (dy > 0 && _issue.GetVelocity().y < 0))
            {
                _issue.AddVelocity(Vector2f(0.0f, dy));
            }
            _issue.SetVelocity(Vector2f(_issue.GetVelocity().x, 0.0f));
        }
    }
}
