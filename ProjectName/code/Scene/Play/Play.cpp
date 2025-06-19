#include <DxLib.h>
#include <thread>
#include "Play.h"
#include "KeyStatus/KeyStatus.h"
#include "ObjectManager/ObjectManager.h"
#include "Loading/LoadingContext.h"
#include "Character/Player/Player.h"
#include "Map/Map.h"
#include "Title/Title.h"

namespace scene
{
    Play::Play()
    {
        //オブジェクト追加
        objManager->AddObject(new object::Player);
        objManager->AddObject(new object::Map);

        task::LoadingContext::Get()->WatchProgress();
    }

    void Play::Init()
    {
        objManager->InitBeforeUpdate();
    }

    std::shared_ptr<SceneBase> Play::Update()
    {
        //Eキーが押されていたらシーン移動
        if (input::KeyStatus::DecisionKeyState(keyType.E, ON_PRESS))
        {
            return std::make_shared<Title>();
        }

        objManager->Update();
        return shared_from_this();
    }

    void Play::Draw()
    {
        objManager->Draw();
    }
}