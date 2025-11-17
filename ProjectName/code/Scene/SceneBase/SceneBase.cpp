module;
#include <DxLib.h>

module Scene.SceneBase;

namespace scene
{
    SceneBase::SceneBase()
    {
        m_objManager = std::make_unique<object::ObjectManager>();
    }

    SceneBase::~SceneBase() = default;
}
