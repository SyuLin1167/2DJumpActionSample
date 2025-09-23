#include "TileColliderVisitor.h"
#include "TileCollider.h"

namespace col2d
{
    void TileColliderVisitor::Visit(RectCollider& _collider)
    {
        if (!issue.GetColliderDef()->isActive || !_collider.GetColliderDef()->isActive)
        {
            return;
        }
        bool shouldEvent = false;

        // 移動量からサブステップ数を決める
        Vector2f vel = _collider.GetVelocity();
        float longest = std::fmax(std::abs(vel.x), std::abs(vel.y));
        float stepMax = issue.GetTileSize().Half().x;
        int N = std::fmax(1, static_cast<int>(std::ceil(longest / stepMax)));
        vel /= N;

        for (int i = 0; i < N; ++i)
        {
            auto rect = _collider.GetRect();
            rect.pos += vel;
            
            if (issue.IsColliding(rect))
            {
                ColliderDef* def = issue.GetColliderDef();
                auto hitTileKyes = issue.GetHitTileKeys();

                while (!hitTileKyes.empty())
                {
                    auto& [key, index] = hitTileKyes.front();
                    hitTileKyes.pop();
                    auto tileInfo = issue.GetTileInfo(key, index);

                    if (!tileInfo || !tileInfo->collider)
                    {
                        continue;
                    }

                    if (_collider.IsColliding(*tileInfo->collider))
                    {
                        resolver.Resolve(_collider, *tileInfo->collider, tileInfo->adjacentFlag);
                        shouldEvent = true;
                    }
                }
            }
        }
        if (shouldEvent)
        {
            _collider.TriggerEvent(issue.GetFilter().category);
        }
        _collider.AddVelocity();
    }
}
