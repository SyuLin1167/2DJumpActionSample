module;
#include <DxLib.h>

module Scene.SceneManager;

import MyLib.KeyStatus;
import Scene.SceneBase;
import Scene.Title;
import Asset.Graph;
import GameSystem.FrameRate;

namespace scene
{
    SceneManager::SceneManager()
        : m_nextScene()
        , m_graph(new asset::Graph)
    {
        // 初期化
        m_graph->CreateHandle("background", "bg.png");
        gameSystem::FrameRate::Instance();

        //最初のシーンをタイトルに設定
        m_nowScene.emplace(new Title);
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
        gameSystem::FrameRate::Instance().CalcFrameRate();
        input::KeyStatus::UpdateKeyState();
        m_nextScene = m_nowScene.top()->Update();
    }

    void SceneManager::Draw()
    {
        //描画
        ClearDrawScreen();
        DrawGraph(0, 0, m_graph->GetHandle("background"), true);
        m_nowScene.top()->Draw();
        clsDx();
        SetFontSize(32);
        DrawFormatString(10, 1020, GetColor(50, 250, 200), "Eキーでシーン遷移");
#ifdef _DEBUG
        gameSystem::FrameRate::Instance().DrawFrameRate();
#endif // _DEBUG
        ScreenFlip();
    }

    void SceneManager::ChangeScene()
    {
        //シーン切り替え処理
        if (m_nextScene.get() != m_nowScene.top().get())
        {
            m_nowScene.pop();
            m_nowScene.emplace(m_nextScene);
            m_nowScene.top()->Init();
        }
    }
}