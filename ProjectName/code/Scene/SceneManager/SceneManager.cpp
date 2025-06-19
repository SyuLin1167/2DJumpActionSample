#include <DxLib.h>
#include "SceneManager.h"
#include "FrameRate/FrameRate.h"
#include "KeyStatus/KeyStatus.h"
#include "SceneBase/SceneBase.h"
#include "Title/Title.h"

namespace scene
{
    SceneManager::SceneManager()
        : nextScene()
        , graph(new asset::Graph)
    {
        graph->CreateHandle("background", "bg.png");

        gameSystem::FrameRate::CreateInstance();
        nowScene.emplace(new Title);
    }

    void SceneManager::GameLoop()
    {
        //ゲームループ
        while (!ProcessMessage() && !input::KeyStatus::DecisionKeyState(keyType.ESCAPE, ON_PRESS))
        {
            Update();
            Draw();
            ChangeScene();
        }
    }

    void SceneManager::Update()
    {
        //更新処理
        gameSystem::FrameRate::Self().CalcFrameRate();
        input::KeyStatus::UpdateKeyState();
        nextScene = nowScene.top()->Update();
    }

    void SceneManager::Draw()
    {
        //描画
        ClearDrawScreen();
        DrawGraph(0, 0, graph->GetHandle("background"), true);
        nowScene.top()->Draw();
        clsDx();
        SetFontSize(32);
        DrawFormatString(10, 1020, GetColor(50, 250, 200), "Eキーでシーン遷移");
#ifdef _DEBUG
        gameSystem::FrameRate::Self().DrawFrameRate();
#endif // _DEBUG
        ScreenFlip();
    }

    void SceneManager::ChangeScene()
    {
        //シーン切り替え処理
        if (nextScene.get() != nowScene.top().get())
        {
            nowScene.pop();
            nowScene.emplace(nextScene);
            nowScene.top()->Init();
        }
    }
}