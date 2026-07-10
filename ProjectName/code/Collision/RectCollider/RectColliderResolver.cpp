module Collider.RectColliderResolver;
import Collider.RectCollider;
import Collider.CircleCollider;
import MyLib.Math.Vector2;

using namespace math;

namespace col2d
{
    void RectColliderResolver::Resolve(RectCollider& issue, const RectCollider& other)
    {
        // 差分を算出
        Vector2f diffX
        {
            other.GetRect().Left() - issue.GetRect().Right(),
            other.GetRect().Right() - issue.GetRect().Left()
        };
        Vector2f diffY
        {
            other.GetRect().Top() - issue.GetRect().Bottom(),
            other.GetRect().Bottom() - issue.GetRect().Top()
        };

        // 軸ごと押し戻し量を出す
        float dx = (std::abs(diffX.x) < std::abs(diffX.y)) ? diffX.x : diffX.y;
        float dy = (std::abs(diffY.x) < std::abs(diffY.y)) ? diffY.x : diffY.y;

        // 対角同値は何もしない
        if (std::abs(dx) == std::abs(dy))
        {
            return;
        }

        // 最も近い方向に押し戻す
        if (std::abs(dx) < std::abs(dy))
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

    void RectColliderResolver::Resolve(RectCollider& issue, const CircleCollider& other)
    {
        // 中心から最も近い辺を求める
        Vector2f nearest
        {
            std::clamp(other.GetCircle().center.x, issue.GetRect().Left(), issue.GetRect().Right()),
            std::clamp(other.GetCircle().center.y, issue.GetRect().Top(), issue.GetRect().Bottom())
        };

        // 差分を算出
        Vector2f diff = nearest - other.GetCircle().center;
        float distSq = diff.LengthSq();
        float penetration = other.GetCircle().radius - std::sqrt(distSq);
        
        // 押し戻し方向と量を計算
        Vector2f normal = diff.Norm();
        Vector2f push = normal * penetration;
        issue.AddVelocity(push);

        // 押し戻し後の速度成分除去
        Vector2f v = issue.GetVelocity();
        float vn = v.Dot(normal);
        issue.SetVelocity(v - normal * vn);
    }
}
