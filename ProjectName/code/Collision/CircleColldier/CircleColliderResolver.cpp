module Collider.CircleColliderResolver;
import MyLib.Math.Vector2;
import Collider.CircleCollider;
import Collider.RectCollider;

using namespace math;

namespace col2d
{
    void CircleColliderResolver::Resolve(CircleCollider& issue, const RectCollider& other)
    {
        // ·•ª‚ðŽZo
        Vector2f diff = issue.GetCircle().center - other.GetRect().Center();

        // Ž²‚²‚Æ‚É‰Ÿ‚µ–ß‚µ•ûŒü‚ðo‚·
        Vector2f push = { 0.0f, 0.0f };
        if (std::abs(diff.x) > std::abs(diff.y))
        {
            push.x = (diff.x < 0) ? -other.GetRect().size.Half().x : other.GetRect().size.Half().x;
        }
        else
        {
            push.y = (diff.y < 0) ? -other.GetRect().size.Half().y : other.GetRect().size.Half().y;
        }

        issue.AddVelocity(push);

        // ‰Ÿ‚µ–ß‚µŒã‚Ì‘¬“x¬•ªœ‹Ž
        Vector2f normal = push.Norm();
        Vector2f v = issue.GetVelocity();
        float vn = v.Dot(normal);
        issue.SetVelocity(v - normal * vn);
    }

    void CircleColliderResolver::Resolve(CircleCollider& issue, const CircleCollider& other)
    {
        // ·•ª‚ðŽZo
        Vector2f diff = issue.GetCircle().center - other.GetCircle().center;
        float distSq = diff.LengthSq();
        float rSum = issue.GetCircle().radius + other.GetCircle().radius;

        // ‰Ÿ‚µ–ß‚µ—Ê‚Æ•ûŒü‚ðŒvŽZ
        float dist = std::sqrt(distSq);
        float penetration = rSum - dist;
        Vector2f normal = diff / dist;
        Vector2f push = normal * penetration;

        issue.AddVelocity(push);

        // ‰Ÿ‚µ–ß‚µŒã‚Ì‘¬“x¬•ªœ‹Ž
        Vector2f v = issue.GetVelocity();
        float vn = v.Dot(normal);
        issue.SetVelocity(v - normal * vn);
    }
}