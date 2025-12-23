module;
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
        //リソースフォルダをデバッグ・リリースフォルダへコピー
        fs::path resourcesSrc = AppCtx::FileSystem().GetResourcesDir();

        // Debugフォルダへコピー
        fs::path resourcesDst = AppCtx::FileSystem().GetResourcesDir() / "../Debug/resources";
        AppCtx::FileSystem().CopyDir(resourcesSrc, resourcesDst);

        // Releaseフォルダへコピー
        resourcesDst = AppCtx::FileSystem().GetResourcesDir() / "../Release/resources";
        AppCtx::FileSystem().CopyDir(resourcesSrc, resourcesDst);
#endif // DEBUG

        //ゲーム実行に必要なクラスのインスタンスを生成、初期化
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
        //ライブラリ初期化
        if (!m_library->InitSuccess())
        {
            return -1;
        }

        //ゲームループ
        m_scene->GameLoop();

        //ソフトの正常終了
        return _CrtDumpMemoryLeaks();
    }
}