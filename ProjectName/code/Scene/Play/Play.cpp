module;
#include <DxLib.h>
#include <thread>

module Scene.Play;

import MyLib.KeyStatus;
import Scene.Title;
import Object.ObjectManager;
import Object.Player;
import Object.Map;

namespace scene
{
    Play::Play()
    {
        //オブジェクト追加
        m_objManager->AddObject(new object::Player);
        m_objManager->AddObject(new object::Map);
    }

    void Play::Init()
    {
        m_objManager->InitBeforeUpdate();
    }

    std::shared_ptr<SceneBase> Play::Update()
    {
        //Eキーが押されていたらシーン移動
        if (input::KeyStatus::DecisionKeyState(keyType.E, ON_PRESS))
        {
            return std::make_shared<Title>();
        }

        m_objManager->Update();
        return shared_from_this();
    }

    void Play::Draw()
    {
        m_objManager->Draw();
    }
}