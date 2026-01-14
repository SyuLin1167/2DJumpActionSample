・ｿmodule;
#include <DxLib.h>

module Scene.SceneManager;

import MyLib.KeyStatus;
import MyLib.MouseStatus;
import Scene.Title;
import GameSystem.FrameRate;
import <memory>;
import <variant>;

using namespace gameSystem;
using namespace input;

namespace scene
{
    SceneManager::SceneManager()
        : m_pendingCmd()
        , m_isRunning(true)
    {
        //譛蛻昴・繧ｷ繝ｼ繝ｳ繧偵ち繧､繝医Ν縺ｫ險ｭ螳・        m_nowScene.emplace(std::make_shared<Title>());
    }

    void SceneManager::GameLoop()
    {
        //繧ｲ繝ｼ繝繝ｫ繝ｼ繝・        while (!ProcessMessage() && m_isRunning)
        {
            Update();
            Draw();
            ChangeScene();
        }
    }

    void SceneManager::Update()
    {
        //譖ｴ譁ｰ蜃ｦ逅・        FrameRate::CalcFrameRate();
        KeyStatus::UpdateKeyState();
        MouseStatus::UpdateMouseState();
        m_pendingCmd = m_nowScene.top()->Update();
    }

    void SceneManager::Draw()
    {
        //謠冗判
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
        // 繝輔Ξ繝ｼ繝邨らｫｯ縺ｧ繧ｳ繝槭Φ繝蛾←逕ｨ
        std::visit(
            [this](auto&& cmd)
            {
                using T = std::decay_t<decltype(cmd)>;
                if constexpr (std::is_same_v<T, std::monostate>)
                {
                    // 菴輔ｂ縺励↑縺・                }
                else if constexpr (std::is_same_v<T, CmdPush>)
                {
                    // 譁ｰ縺励＞繧ｷ繝ｼ繝ｳ繧堤ｩ阪・
                    auto next = cmd.build ? cmd.build() : nullptr;
                    if (next)
                    {
                        m_nowScene.push(next);
                        m_nowScene.top()->Init();
                    }
                }
                else if constexpr (std::is_same_v<T, CmdReplace>)
                {
                    // 迴ｾ蝨ｨ縺ｮ繧ｷ繝ｼ繝ｳ繧堤ｽｮ縺肴鋤縺医ｋ
                    auto next = cmd.build ? cmd.build() : nullptr;
                    if (next)
                    {
                        if (!m_nowScene.empty())
                        {
                            m_nowScene.pop();
                        }
                        m_nowScene.push(next);
                        m_nowScene.top()->Init();
                    }
                }
                else if constexpr (std::is_same_v<T, CmdPop>)
                {
                    // 迴ｾ蝨ｨ縺ｮ繧ｷ繝ｼ繝ｳ繧貞叙繧企勁縺・                    if (!m_nowScene.empty())
                    {
                        m_nowScene.pop();
                    }
                }
                else if constexpr (std::is_same_v<T, CmdQuit>)
                {
                    // 繧ｲ繝ｼ繝邨ゆｺ・                    PostQuitMessage(0);
                    m_isRunning = false;
                }
            },
            m_pendingCmd);

        // 繧ｳ繝槭Φ繝峨ｒ繧ｯ繝ｪ繧｢
        m_pendingCmd = std::monostate{};
    }
}