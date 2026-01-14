・ｿmodule;
#include <DxLib.h>
#include <json.hpp>
#include <fstream>
#include <functional>
#include <algorithm>

module Object.Map;

import <future>;

import MyLib.Loading.LoadingContext;
import MyLib.Math.Vector2;
import MyLib.TileChunkUtil;
import GameSystem.Camera;
import Asset.DivisionGraph;
import GameSystem.Window;

using namespace gameSystem;
using namespace math;

namespace object
{
    Map::Map()
    {
        // 繝槭ャ繝玲ｧ区・隱ｭ縺ｿ霎ｼ縺ｿ
        auto path = AppCtx::FileSystem().Resolve("data://MapTip.csv");
        auto mapDataSf = AppCtx::FileSystem().csvIO.CreateArrayAsync<size_t>(path).share();

        // 繧ｿ繧､繝ｫ諠・ｱ隱ｭ縺ｿ霎ｼ縺ｿ
        auto mapInfoSf = AppCtx::FileSystem().jsonIO.LoadAsync(AppCtx::FileSystem().Resolve("data://MapData")).share(); 

        // 譛邨ら噪縺ｪ MapInfo 繧貞ｱ翫￠繧九◆繧√・ promise/future
        auto infoPromise = std::make_shared<std::promise<object::MapInfo>>();

        // 繝槭ャ繝礼函謌・        task::LoadingContext::Get()->AddTask(task::INIT, [this, mapDataSf, mapInfoSf, infoPromise]() {
            // 繝槭ャ繝励ョ繝ｼ繧ｿ蜿門ｾ・            const auto& dataArray = mapDataSf.get();
            m_mapInfo.FromJson(mapInfoSf.get());

            // 繝√Ε繝ｳ繧ｯ繧ｵ繧､繧ｺ繧貞叙蠕・            m_mapInfo.chunkSize = Window::GetWindowData()->SIZE / m_mapInfo.tileSize.Half();

            
            infoPromise->set_value(m_mapInfo);

            //繝√Ε繝ｳ繧ｯ蛹悶＠縺ｦ繝槭ャ繝励ョ繝ｼ繧ｿ譬ｼ邏・            m_mapData = tile::BuildChunkedGrid<size_t>(
                m_mapInfo.mapSize.x,
                m_mapInfo.mapSize.y,
                m_mapInfo.chunkSize,
                [&](size_t, size_t, size_t gidx, size_t, size_t)->std::optional<size_t>
                {
                    return std::optional<size_t>{ dataArray[gidx] };
                });
            });

        // 蠖薙◆繧雁愛螳夂函謌・        col2d::ColliderDef def;
        def.isActive = true;
        colID = ObjectContext::ColMgr().CreateTileCollider(&def, infoPromise->get_future().share(), "MapTip.csv", MyObjectTag());

        // 繝槭ャ繝礼判蜒剰ｪｭ縺ｿ霎ｼ縺ｿ
        AppCtx::AssetMgr().LoadAsync<asset::DivisionGraph>("map", "map.png");
    }

    Map::~Map()
    {
        AppCtx::AssetMgr().DeleteHandle<asset::DivisionGraph>("map");
    }

    void Map::Init()
    {
        // 繝ｯ繝ｼ繝ｫ繝峨し繧､繧ｺ險ｭ螳・        Vector2f worldSize
        {
            m_mapInfo.mapSize.x * m_mapInfo.tileSize.x,
            m_mapInfo.mapSize.y * m_mapInfo.tileSize.y
        };
        gameSystem::Camera::Instance().SetWorldSize(worldSize);

        // 陦晉ｪ√・繧ｹ繧ｯ霑ｽ蜉
        ObjectContext::ColMgr().AddMask(colID, col2d::RECT, PLAYER);
    }

    void Map::Draw()
    {
        // 繝槭ャ繝玲悴逕滓・縺ｪ繧画緒逕ｻ縺励↑縺・        if (m_mapData.empty())
        {
            return;
        }

        // 繧ｫ繝｡繝ｩ繧ｪ繝輔そ繝・ヨ蜿門ｾ・        Vector2f camOffset = gameSystem::Camera::Instance().GetOffset();
        const auto winSize = Window::GetWindowData()->SIZE;

        // 謠冗判遽・峇邂怜・
        const int startTileX = (std::max)(0, static_cast<int>(camOffset.x / m_mapInfo.tileSize.x));
        const int startTileY = (std::max)(0, static_cast<int>(camOffset.y / m_mapInfo.tileSize.y));
        const int endTileX = (std::min)(static_cast<int>(m_mapInfo.mapSize.x) - 1,
            static_cast<int>((camOffset.x + winSize.x) / m_mapInfo.tileSize.x) + 1);
        const int endTileY = (std::min)(static_cast<int>(m_mapInfo.mapSize.y) - 1,
            static_cast<int>((camOffset.y + winSize.y) / m_mapInfo.tileSize.y) + 1);

        // 謠冗判遽・峇險ｭ螳・        rangeX = { static_cast<size_t>(startTileX), static_cast<size_t>(endTileX) };
        rangeY = { static_cast<size_t>(startTileY), static_cast<size_t>(endTileY) };

        // 謠冗判繝ｫ繝ｼ繝・        for (size_t i = rangeY.first; i <= rangeY.second; i++)
        {
            for (size_t j = rangeX.first; j <= rangeX.second; j++)
            {
                // 繝√Ε繝ｳ繧ｯ縺ｫ豐ｿ縺｣縺溘く繝ｼ繧堤函謌・                auto key = (static_cast<uint64_t>(i / m_mapInfo.chunkSize.y) << 32) | static_cast<uint64_t>(j / m_mapInfo.chunkSize.x);

                // 繝ｭ繝ｼ繧ｫ繝ｫ繧､繝ｳ繝・ャ繧ｯ繧ｹ縺ｧ繧ｿ繧､繝ｫ蜿門ｾ・                const size_t localY = i % m_mapInfo.chunkSize.y;
                const size_t localX = j % m_mapInfo.chunkSize.x;
                const size_t localIndex = localY * m_mapInfo.chunkSize.x + localX;

                // 蠎ｧ讓吶↓豐ｿ縺｣縺溘ワ繝ｳ繝峨Ν蜿門ｾ・                auto mapIt = m_mapData.find(key);
                if (mapIt == m_mapData.end()) continue;
                int handle = AppCtx::AssetMgr().Fetch<asset::DivisionGraph>()->GetHandle("map", mapIt->second.at(localIndex));

                // 繝√Ε繝ｳ繧ｯ縺ｫ豐ｿ縺｣縺溷ｺｧ讓吶↓謠冗判
                float x = j * m_mapInfo.tileSize.x;
                float y = i * m_mapInfo.tileSize.y;
                Vector2f camPos = gameSystem::Camera::Instance().WorldToScreen({ x, y });
                DrawGraph(static_cast<int>(camPos.x), static_cast<int>(camPos.y), handle, true);
            }
        }
    }

    void Map::CalcDrawRange(int pos, std::pair<size_t, size_t>& range, size_t length)
    {
        // 遽・峇邂怜・
        if (length == 0)
        {
            range = {0, 0};
            return;
        }
        const int maxIndex = static_cast<int>(length) - 1;
        range.first  = static_cast<size_t>(std::clamp(pos - 5, 0, maxIndex));
        range.second = static_cast<size_t>(std::clamp(pos + 5, 0, maxIndex));
    }
}
