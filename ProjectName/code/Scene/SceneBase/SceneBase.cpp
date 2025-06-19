#include "SceneBase.h"
#include "ObjectManager/ObjectManager.h"

namespace scene
{
    SceneBase::SceneBase()
    {
        objManager = std::make_unique<object::ObjectManager>();
    }

    SceneBase::~SceneBase() = default;
}
