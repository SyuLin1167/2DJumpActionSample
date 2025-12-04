module;
#include <DxLib.h>

module Scene.Result;

import <memory>;
import Scene.Result;
import Scene.Title;
import MyLib.KeyStatus;
import AppContext;
import Asset.Graph;

namespace scene
{
    Result::Result()
    {
        gameSystem::AppCtx::AssetMgr().LoadAsync<asset::Graph>("Result", "Result.png");
    }

    std::shared_ptr<SceneBase> Result::Update()
    {
        // Rキーでリトライ（タイトルへ）
        if (input::KeyStatus::CheckKey(keyType.R, ON_PRESS))
        {
            return std::make_shared<Title>();
        }
        return shared_from_this();
    }

    void Result::Draw()
    {
        // 背景描画
        DrawGraph(0, 0, gameSystem::AppCtx::AssetMgr().Fetch<asset::Graph>()->GetHandle("Result"), FALSE);
        DrawFormatString(500, 300, GetColor(255, 255, 255), "CLEAR! Rキーでタイトルへ");
    }
}