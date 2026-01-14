・ｿmodule;
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
        //繧ｪ繝悶ず繧ｧ繧ｯ繝郁ｿｽ蜉
        m_objManager->AddObject(new object::Player);
        m_objManager->AddObject(new object::Enemy);
        m_objManager->AddObject(new object::Map);
        m_objManager->AddObject(new object::Goal(m_cleared));

        // 閭梧勹逕ｻ蜒剰ｪｭ縺ｿ霎ｼ縺ｿ
        gameSystem::AppCtx::AssetMgr().LoadAsync<asset::Graph>("background", "Play.png");
    }

    Play::~Play()
    {
        // 閭梧勹逕ｻ蜒上ワ繝ｳ繝峨Ν蜑企勁
        gameSystem::AppCtx::AssetMgr().DeleteHandle<asset::Graph>("background");
    }

    void Play::Init()
    {
        m_objManager->InitBeforeUpdate();
    }

    SceneCmd Play::Update()
    {
        // 繧ｪ繝悶ず繧ｧ繧ｯ繝域峩譁ｰ
        m_objManager->Update();

        // 繧ｯ繝ｪ繧｢蠕後・逕ｻ髱｢縺ｸ遘ｻ蜍・        if (m_cleared)
        {
            return CmdReplace{ [](){ return std::make_shared<Result>(); } };
        }

        // 邯咏ｶ・        return std::monostate{};
    }

    void Play::Draw()
    {
        DrawScrollingBackground();
        m_objManager->Draw();
    }

    void Play::DrawScrollingBackground(float parallax)
    {
        // 繧ｫ繝｡繝ｩ繧ｪ繝輔そ繝・ヨ蜿門ｾ・        auto camOffset = gameSystem::Camera::Instance().GetOffset();

        // 繧ｰ繝ｩ繝輔い繧ｻ繝・ヨ蜿門ｾ・        auto graph = gameSystem::AppCtx::AssetMgr().Fetch<asset::Graph>();
        if (!graph)
        {
            return;
        }

        // 閭梧勹逕ｻ蜒上ワ繝ｳ繝峨Ν蜿門ｾ・        int bgHandle = graph->GetHandle("background");
        if (bgHandle < 0)
        {
            return;
        }

        // 閭梧勹繧ｵ繧､繧ｺ縺ｨ繧ｦ繧｣繝ｳ繝峨え繧ｵ繧､繧ｺ蜿門ｾ・        int bgW = 0, bgH = 0;
        GetGraphSize(bgHandle, &bgW, &bgH);
        auto winSize = Window::GetWindowData()->SIZE;

        // 繧ｫ繝｡繝ｩ繧ｪ繝輔そ繝・ヨ縺ｫ蟇ｾ縺励※閭梧勹縺ｮ繝代Λ繝ｩ繝・け繧ｹ遘ｻ蜍暮㍼
        int scrollX = static_cast<int>(-camOffset.x * parallax);
        int drawY = static_cast<int>(-camOffset.y * parallax);

        // Y縺ｯ縺昴・縺ｾ縺ｾ謠冗判・亥ｿ・ｦ√↑繧牙酔讒倥↓繧ｿ繧､繝ｫ蛹門庄閭ｽ・・        int drawX1 = scrollX % bgW;
        drawX1 = (drawX1 + bgW < 0) ? drawX1 += bgW : drawX1;
        drawX1 = (drawX1 > bgW) ? drawX1 -= bgW : drawX1;

        int drawX2 = scrollX % bgW + bgW;
        drawX2 = (drawX2 + bgW < 0) ? drawX2 += bgW : drawX2;
        drawX2 = (drawX2 > bgW) ? drawX2 -= bgW : drawX2;

        // 2譫壹〒豌ｴ蟷ｳ繝ｫ繝ｼ繝・        DrawGraph(drawX1, drawY, bgHandle, true);
        DrawGraph(drawX2, drawY, bgHandle, true);

        // 逕ｻ髱｢蟷・ｒ隕・≧縺溘ａ縺ｫ霑ｽ蜉謠冗判
        if (winSize.x > bgW)
        {
            DrawGraph(drawX2 + bgW, drawY, bgHandle, true);
        }
    }
}