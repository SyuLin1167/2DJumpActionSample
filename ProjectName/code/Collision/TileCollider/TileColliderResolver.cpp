#include "TileColliderResolver.h"

#include <cmath>
#include <limits>

#include "TileCollider.h"

namespace col2d
{
    void TileColliderResolver::Resolve(RectCollider& issue, const RectCollider& other, uint8_t adjacentFlag)
    {
        // めり込み量を計算
        Vector2f diffX{};
        diffX.x = other.GetRect().Left() - issue.GetRect().Right();
        diffX.y = other.GetRect().Right() - issue.GetRect().Left();
        Vector2f diffY{};
        diffY.x = other.GetRect().Top() - issue.GetRect().Bottom();
        diffY.y = other.GetRect().Bottom() - issue.GetRect().Top();

        // 隣接フラグがある方向は無視する
        if (adjacentFlag & TileFlag::LEFT)
        {
            diffX.x = std::numeric_limits<float>::infinity();
        }
        if (adjacentFlag & TileFlag::RIGHT)
        {
            diffX.y = std::numeric_limits<float>::infinity();
        }
        if (adjacentFlag & TileFlag::TOP)
        {
            diffY.x = std::numeric_limits<float>::infinity();
        }
        if (adjacentFlag & TileFlag::BOTTOM)
        {
            diffY.y = std::numeric_limits<float>::infinity();
        }
        float dx = (std::abs(diffX.x) < std::abs(diffX.y)) ? diffX.x : diffX.y;
        float dy = (std::abs(diffY.x) < std::abs(diffY.y)) ? diffY.x : diffY.y;

        if (fabs(dx) == fabs(dy))
        {
            return;
        }

        //最も近い方向に押し戻す
        if (fabs(dx) < fabs(dy))
        {
            // 同じ方向への押し戻しは受け付けないようにする
            if ((dx < 0 && issue.GetVelocity().x > 0) || (dx > 0 && issue.GetVelocity().x < 0))
            {
                issue.AddVelocity(Vector2f(dx, 0.0f));
            }
            issue.SetVelocity(Vector2f(0.0f, issue.GetVelocity().y));
        }
        else
        {
            // 同じ方向への押し戻しは受け付けないようにする
            if ((dy < 0 && issue.GetVelocity().y > 0) || (dy > 0 && issue.GetVelocity().y < 0))
            {
                issue.AddVelocity(Vector2f(0.0f, dy));
            }
            issue.SetVelocity(Vector2f(issue.GetVelocity().x, 0.0f));
        }
    }
}
