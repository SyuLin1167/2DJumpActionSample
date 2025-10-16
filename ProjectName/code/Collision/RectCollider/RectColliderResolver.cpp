module Collider.RectColliderResolver;
import Collider.RectCollider;
import MyLib.Math.Vector2;

using namespace math;

namespace col2d
{
    void RectColliderResolver::Resolve(RectCollider& issue, const RectCollider& other)
    {
        if (issue.GetSweptRect().AABB(other.GetRect()))
        {
            // 差分の算出
            Vector2f diffX{};
            diffX.x = other.GetRect().Left() - issue.GetSweptRect().Right();
            diffX.y = other.GetRect().Right() - issue.GetSweptRect().Left();
            Vector2f diffY{};
            diffY.x = other.GetRect().Top() - issue.GetSweptRect().Bottom();
            diffY.y = other.GetRect().Bottom() - issue.GetSweptRect().Top();

            // 軸ごと押し戻し量を出す
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
}
