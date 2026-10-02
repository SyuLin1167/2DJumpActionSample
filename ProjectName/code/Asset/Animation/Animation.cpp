module;

#include <DxLib.h>

module Asset.Animation;

import Asset.DivisionGraph;
import GameSystem.FrameRate;
import MyLib.Loading.LoadingContext;
import AppContext;

using namespace gameSystem;

namespace asset
{
    Animation::Animation()
        :m_divGraph(std::make_unique<DivisionGraph>())
    {
        //処理なし
    }

    void Animation::CreateHandle(std::string handleName, std::string graphName)
    {
        m_divGraph->CreateHandle(handleName, graphName);
    }

    void Animation::CreateHandleAsync(std::string handleName, std::string graphName)
    {
        m_divGraph->CreateHandleAsync(handleName, graphName);
    }

    void Animation::AddAnim(const AnimationDef& animDef)
    {
        m_animations[animDef.name] = { m_divGraph->GetHandle(animDef.name), animDef };
        m_animations[animDef.name].second.endFrame = m_divGraph->GetTotalDiv(animDef.name);
    }

    void Animation::AddAnimCategory(const std::string& category, const std::vector<AnimationDef> animDefs)
    {
        for (auto& def : animDefs)
        {
            m_animations[def.name] = { m_divGraph->GetHandle(category), def };
        }
    }

    void Animation::DeleteHandle(std::string name)
    {
        m_divGraph->DeleteHandle(name);
    }

    void Animation::DeleteAnim(const std::string& animName)
    {
        m_divGraph->DeleteHandle(animName);
        m_animations.erase(animName);
    }
}