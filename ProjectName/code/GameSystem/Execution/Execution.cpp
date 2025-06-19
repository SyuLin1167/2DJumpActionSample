#include <Dxlib.h>
#include "Execution.h"
#include "Window/Window.h"
#include "Library/Library.h"
#include "KeyStatus/KeyStatus.h"
#include "SceneManager/SceneManager.h"
#include "FileIO/ExeFilePath.h"

namespace fs = std::filesystem;

namespace gameSystem
{
    Execution::Execution()
    {
        //ゲーム実行に必要なクラスのインスタンスを生成、初期化
        Window::InitInstance();
        library.reset(new Library);
        input::KeyStatus::InitInstance();
        scene.reset(new scene::SceneManager);

        //実行に必要なデータファイルを実行ファイルの場所に複製
        fs::path dataFile = file::GetExeDirectory() / "../../data";
        fs::path dataDest = file::GetExeDirectory() / dataFile.filename();
        fs::copy(dataFile, dataDest, fs::copy_options::recursive | fs::copy_options::overwrite_existing);

        //実行に必要な素材ファイルを実行ファイルの場所に複製
        fs::path assetsFile = file::GetExeDirectory() / "../../assets";
        fs::path assetsDest = file::GetExeDirectory() / assetsFile.filename();
        fs::copy(assetsFile, assetsDest, fs::copy_options::recursive | fs::copy_options::overwrite_existing);

        //実行に必要なシェーダーファイルを実行ファイルの場所に複製
        fs::path shaderFile = file::GetExeDirectory() / "../../shader";
        fs::path shaderDest = file::GetExeDirectory() / shaderFile.filename();
        fs::copy(shaderFile, shaderDest, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
    }

    Execution::~Execution() = default;

    int Execution::Run()
    {
        //ライブラリ初期化
        if (!library->InitSuccess())
        {
            return -1;
        }

        //ゲームループ
        scene->GameLoop();

        //ソフトの正常終了
        return _CrtDumpMemoryLeaks();
    }
}