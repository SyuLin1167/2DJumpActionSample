module;
#include <DxLib.h>

module Scene.SceneManager;

import MyLib.KeyStatus;
import Scene.SceneBase;
import Scene.Title;
import GameSystem.FrameRate;

using namespace gameSystem;
using namespace input;

namespace scene
{
    SceneManager::SceneManager()
        : m_nextScene()
    {
        //最初のシーンをタイトルに設定
        m_nowScene.emplace(new Title);
    }

    void SceneManager::GameLoop()
    {
        //ゲームループ
        while (!ProcessMessage() && !KeyStatus::CheckKey(keyType.ESCAPE, ON_PRESS))
        {
            Update();
            Draw();
            ChangeScene();
        }
    }

    void SceneManager::Update()
    {
        //更新処理
        FrameRate::CalcFrameRate();
        KeyStatus::UpdateKeyState();
        m_nextScene = m_nowScene.top()->Update();
    }

    void SceneManager::Draw()
    {
        //描画
        ClearDrawScreen();
        clsDx();
        m_nowScene.top()->Draw();

#ifdef _DEBUG
        FrameRate::DrawFrameRate();
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