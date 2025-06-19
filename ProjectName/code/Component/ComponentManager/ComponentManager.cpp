#include "ComponentManager.h"
#include "ComponentBase/ComponentBase.h"

namespace component
{
    void ComponentManager::Update(const float& _deltaTime)
    {
        for (auto& component : components)
        {
            component.second->Update(_deltaTime);
        }
    }
}
