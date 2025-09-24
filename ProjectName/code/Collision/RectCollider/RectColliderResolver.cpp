#include "RectColliderResolver.h"
#include "RectCollider.h"

namespace col2d
{
    void RectColliderResolver::Resolve(RectCollider& _issue, const RectCollider& _other)
    {
        if (_issue.GetSweptRect().AABB(_other.GetRect()))
        {
            Vector2f diffX{};
            diffX.x = _other.GetRect().Left() - _issue.GetSweptRect().Right();
            diffX.y = _other.GetRect().Right() - _issue.GetSweptRect().Left();
            Vector2f diffY{};
            diffY.x = _other.GetRect().Top() - _issue.GetSweptRect().Bottom();
            diffY.y = _other.GetRect().Bottom() - _issue.GetSweptRect().Top();

            float dx = (fabs(diffX.x) < fabs(diffX.y)) ? diffX.x : diffX.y;
            float dy = (fabs(diffY.x) < fabs(diffY.y)) ? diffY.x : diffY.y;


            if (fabs(dx) == fabs(dy))
            {
                return;
            }

            //Å‚à‹ß‚¢•ûŒü‚É‰Ÿ‚µ–ß‚·
            if (fabs(dx) < fabs(dy))
            {
                // “¯‚¶•ûŒü‚Ö‚Ì‰Ÿ‚µ–ß‚µ‚ÍŽó‚¯•t‚¯‚È‚¢‚æ‚¤‚É‚·‚é
                if ((dx < 0 && _issue.GetVelocity().x > 0) || (dx > 0 && _issue.GetVelocity().x < 0))
                {
                    _issue.AddVelocity(Vector2f(dx, 0.0f));
                }
                _issue.SetVelocity(Vector2f(0.0f, _issue.GetVelocity().y));
            }
            else
            {
                // “¯‚¶•ûŒü‚Ö‚Ì‰Ÿ‚µ–ß‚µ‚ÍŽó‚¯•t‚¯‚È‚¢‚æ‚¤‚É‚·‚é
                if ((dy < 0 && _issue.GetVelocity().y > 0) || (dy > 0 && _issue.GetVelocity().y < 0))
                {
                    _issue.AddVelocity(Vector2f(0.0f, dy));
                }
                _issue.SetVelocity(Vector2f(_issue.GetVelocity().x, 0.0f));

        }
    }
}
