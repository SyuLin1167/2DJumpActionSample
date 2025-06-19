#include "GameObject.h"
#include "FrameRate/FrameRate.h"

namespace object
{
    GameObject::GameObject()
        : assetMgr(new asset::AssetManager)
        , compMgr(new component::ComponentManager)
        , colMgr(new collision::CollisionManager(this))
        , deltaTime(gameSystem::FrameRate::Self().GetDeltaTime())
        , pos()
        , size()
        , velocity()
    {
        state = MainState::ACTIVE;
    }

    GameObject::~GameObject()
    {
    }

    void GameObject::UpdateCollision()
    {
        colMgr->ColliderWith();
    }

    void GameObject::UpdateComponents()
    {
        compMgr->Update(deltaTime);
    }
}
