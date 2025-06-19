#include "ComponentBase.h"
#include "GameObject/GameObject.h"

namespace component
{
    ComponentBase::ComponentBase(object::GameObject* owner)
        : owner(owner)
    {
        //処理なし
    }
}