・ｿmodule;
#include <Dxlib.h>
#include <filesystem>

module GameSystem.Execution;

import GameSystem.Library;
import GameSystem.Window;
import AppContext;
import ObjectContext;
import MyLib.KeyStatus;
import Scene.SceneManager;

namespace fs = std::filesystem;

namespace gameSystem
{
    Execution::Execution()
    {
#ifdef DEBUG
        //繝ｪ繧ｽ繝ｼ繧ｹ繝輔か繝ｫ繝繧偵ョ繝舌ャ繧ｰ繝ｻ繝ｪ繝ｪ繝ｼ繧ｹ繝輔か繝ｫ繝縺ｸ繧ｳ繝斐・
        fs::path resourcesSrc = AppCtx::FileSystem().GetResourcesDir();

        // Debug繝輔か繝ｫ繝縺ｸ繧ｳ繝斐・
        fs::path resourcesDst = AppCtx::FileSystem().GetResourcesDir() / "../Debug/resources";
        AppCtx::FileSystem().CopyDir(resourcesSrc, resourcesDst);

        // Release繝輔か繝ｫ繝縺ｸ繧ｳ繝斐・
        resourcesDst = AppCtx::FileSystem().GetResourcesDir() / "../Release/resources";
        AppCtx::FileSystem().CopyDir(resourcesSrc, resourcesDst);
#endif // DEBUG

        //繧ｲ繝ｼ繝螳溯｡後↓蠢・ｦ√↑繧ｯ繝ｩ繧ｹ縺ｮ繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ繧堤函謌舌∝・譛溷喧
        Window::Init();
        m_library = std::make_unique<Library>();
        AppCtx::Activate();
        m_scene = std::make_unique<scene::SceneManager>();
    }

    Execution::~Execution()
    {
        m_scene.reset();
        object::ObjCtx::Deactivate();
        AppCtx::Deactivate();
    }

    int Execution::Run()
    {
        //繝ｩ繧､繝悶Λ繝ｪ蛻晄悄蛹・        if (!m_library->InitSuccess())
        {
            return -1;
        }

        //繧ｲ繝ｼ繝繝ｫ繝ｼ繝・        m_scene->GameLoop();

        //繧ｽ繝輔ヨ縺ｮ豁｣蟶ｸ邨ゆｺ・        return _CrtDumpMemoryLeaks();
    }
}