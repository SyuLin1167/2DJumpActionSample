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
        //ゲーム実行に必要なクラスのインスタンスを生成、初期化
        Window::Init();
        m_library.reset(new Library);
        AppCtx::Activate();
        m_scene.reset(new scene::SceneManager);

        // 実行に必要な resources フォルダを実行ファイルの場所に複製
        // ソリューション階層に存在する resources を exe と同階層にコピー
        fs::path resourcesSrc = AppCtx::FileSystem().GetExeDir() / "../../resources";
        fs::path resourcesDst = AppCtx::FileSystem().GetExeDir() / "resources";
        AppCtx::FileSystem().CopyDir(resourcesSrc, resourcesDst);
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