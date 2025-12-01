module Collider.CircleColliderResolver;
import MyLib.Math.Vector2;
import MyLib.Shape.Rect;
import Collider.CircleCollider;
import Collider.RectCollider;

using namespace math;

namespace col2d
{
    void CircleColliderResolver::Resolve(CircleCollider& issue, const RectCollider& other)
    {
        // ·•ª‚ğZo
        shape::Rect otherRect = other.GetRect();
        Vector2f closestPoint
        {
            std::clamp(issue.GetCircle().center.x, otherRect.Left(), otherRect.Right()),
            std::clamp(issue.GetCircle().center.y, otherRect.Top(), otherRect.Bottom())
        };
        Vector2f diff = issue.GetCircle().center - closestPoint;
        
        // ”»’è‹——£‚Ì“ñæ‚ğŒvZ
        float distSq = diff.LengthSq();
        float radius = issue.GetCircle().radius;
        if (distSq >= radius * radius)
        {
            return;
        }

        // ‰Ÿ‚µ–ß‚µ—Ê‚Æ•ûŒü‚ğŒvZ
        float dist = std::sqrt(distSq);
        float penetration = radius - dist;
        Vector2f push = diff.Norm() * penetration;
        issue.AddVelocity(push);

        // ‰Ÿ‚µ–ß‚µŒã‚Ì‘¬“x¬•ªœ‹
        Vector2f normal = push.Norm();
        Vector2f v = issue.GetVelocity();
        float vn = v.Dot(normal);
        issue.SetVelocity(v - normal * vn);
    }

    void CircleColliderResolver::Resolve(CircleCollider& issue, const CircleCollider& other)
    {
        // ·•ª‚ğZo
        Vector2f diff = issue.GetCircle().center - other.GetCircle().center;
        float distSq = diff.LengthSq();
        float rSum = issue.GetCircle().radius + other.GetCircle().radius;

        // ‰Ÿ‚µ–ß‚µ—Ê‚Æ•ûŒü‚ğŒvZ
        float dist = std::sqrt(distSq);
        float penetration = rSum - dist;
        Vector2f push = diff.Norm() * penetration;

        issue.AddVelocity(push);

        // ‰Ÿ‚µ–ß‚µŒã‚Ì‘¬“x¬•ªœ‹
        Vector2f normal = push.Norm();
        Vector2f v = issue.GetVelocity();
        float vn = v.Dot(normal);
        issue.SetVelocity(v - normal * vn);
    }
}