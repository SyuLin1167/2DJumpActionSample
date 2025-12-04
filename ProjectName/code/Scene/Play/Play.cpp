module;
#include <DxLib.h>
#include <thread>

module Scene.Play;

import MyLib.KeyStatus;
import Scene.Title;
import Scene.Result;
import Object.ObjectManager;
import Object.Player;
import Object.Enemy;
import Object.Map;
import Object.Goal;
import GameSystem.Camera;
import Asset.Graph;
import AppContext;
import GameSystem.Window;
import <algorithm>;

using namespace gameSystem;

namespace scene
{
    Play::Play()
        : m_cleared(false)
    {
        //オブジェクト追加
        m_objManager->AddObject(new object::Player);
        m_objManager->AddObject(new object::Enemy);
        m_objManager->AddObject(new object::Map);
        m_objManager->AddObject(new object::Goal(m_cleared));

        // 背景画像読み込み（非同期）
        gameSystem::AppCtx::AssetMgr().LoadAsync<asset::Graph>("background", "Play.png");
    }

    Play::~Play()
    {
        // 背景画像ハンドル削除
        gameSystem::AppCtx::AssetMgr().DeleteHandle<asset::Graph>("background");
    }

    void Play::Init()
    {
        m_objManager->InitBeforeUpdate();
    }

    std::shared_ptr<SceneBase> Play::Update()
    {
        //Eキーが押されていたらシーン移動
        if (input::KeyStatus::CheckKey(keyType.E, ON_PRESS))
        {
            return std::make_shared<Title>();
        }

        // オブジェクト更新
        m_objManager->Update();

        // クリア後のリトライ（タイトルへ）
        if (m_cleared)
        {
            return std::make_shared<Result>();
        }

        return shared_from_this();
    }

    void Play::Draw()
    {
        // 背景の描画（水平スクロールを2枚で無限ループ）
        const float parallax = 0.5f;
        auto camOffset = gameSystem::Camera::Instance().GetOffset();
        auto graph = gameSystem::AppCtx::AssetMgr().Fetch<asset::Graph>();
        if (graph)
        {
            int bgHandle = graph->GetHandle("background");
            if (bgHandle >= 0)
            {
                // 背景サイズとウィンドウサイズ取得
                int bgW = 0, bgH = 0;
                GetGraphSize(bgHandle, &bgW, &bgH);
                auto winSize = Window::GetWindowData()->SIZE;

                // カメラオフセットに対して背景のパララックス移動量
                int scrollX = static_cast<int>(-camOffset.x * parallax);
                int scrollY = static_cast<int>(-camOffset.y * parallax);

                // Yはそのまま描画（必要なら同様にタイル化可能）
                int drawX1 = scrollX % bgW;
                drawX1 = (drawX1 + bgW < 0) ? drawX1 += bgW : drawX1;
                drawX1 = (drawX1 > bgW) ? drawX1 -= bgW : drawX1;

                int drawX2 = scrollX % bgW + bgW;
                drawX2 = (drawX2 + bgW < 0) ? drawX2 += bgW : drawX2;
                drawX2 = (drawX2 > bgW) ? drawX2 -= bgW : drawX2;

                int drawY = scrollY;

                // 2枚で水平ループ。画面幅を覆うため必要なら追加で描画。
                DrawGraph(drawX1, drawY, bgHandle, true);
                DrawGraph(drawX2, drawY, bgHandle, true);

                // 画面幅が背景幅より大きい場合、さらにもう1枚必要になることがある
                if (winSize.x > bgW)
                {
                    DrawGraph(drawX2 + bgW, drawY, bgHandle, true);
                }
            }
        }

        m_objManager->Draw();
    }
}