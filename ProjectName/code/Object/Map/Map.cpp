module;
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
import Asset.DivisionGraph;
import GameSystem.Window;

using namespace gameSystem;

namespace object
{
    Map::Map()
        : player(nullptr)
    {
        // マップ構成読み込み
        auto path = AppCtx::FileSystem().Resolve("data://MapTip.csv");
        auto mapDataSf = AppCtx::FileSystem().csvIO.CreateArrayAsync<size_t>(path).share();

        // タイル情報読み込み
        auto mapInfoSf = AppCtx::FileSystem().jsonIO.LoadAsync(AppCtx::FileSystem().Resolve("data://MapData")).share(); 

        // 最終的な MapInfo を届けるための promise/future
        auto infoPromise = std::make_shared<std::promise<object::MapInfo>>();

        // マップ生成
        task::LoadingContext::Get()->AddTask(task::INIT, [this, mapDataSf, mapInfoSf, infoPromise]() {
            // マップデータ取得
            const auto& dataArray = mapDataSf.get();
            m_mapInfo.FromJson(mapInfoSf.get());

            // チャンクサイズを取得
            m_mapInfo.chunkSize = Window::Instance().GetWindowData()->SIZE / m_mapInfo.tileSize.Half();

            
            infoPromise->set_value(m_mapInfo);

            //チャンク化してマップデータ格納
            m_mapData = tile::BuildChunkedGrid<size_t>(
                m_mapInfo.mapSize.x,
                m_mapInfo.mapSize.y,
                m_mapInfo.chunkSize,
                [&](size_t, size_t, size_t gidx, size_t, size_t)->std::optional<size_t>
                {
                    return std::optional<size_t>{ dataArray[gidx] };
                });
            });

        // 当たり判定生成
        col2d::ColliderDef def;
        def.isActive = true;
        colID = ObjectContext::ColMgr().CreateTileCollider(&def, infoPromise->get_future().share(), "MapTip.csv", MyObjectTag());

        // マップ画像読み込み
        AppCtx::AssetMgr().LoadAsync<asset::DivisionGraph>("map", "map.png");
    }

    Map::~Map()
    {
        AppCtx::AssetMgr().DeleteHandle<asset::DivisionGraph>("map");
    }

    void Map::Init()
    {
        // 衝突マスク追加
        ObjectContext::ColMgr().AddMask(colID, col2d::RECT, PLAYER);
    }

    void Map::GetReferenceObject(std::function<std::vector<std::shared_ptr<GameObject>>(uint32_t)> referenceObj)
    {
        //プレイヤー参照
        player = referenceObj(PLAYER).begin()->get();
    }

    void Map::Draw()
    {
        // マップ未生成なら描画しない
        if (m_mapData.empty())
        {
            return;
        }

        //描画範囲を算出して描画
        CalcDrawRange(static_cast<int>(player->AccessPos().NowY()) / m_mapInfo.tileSize.x, rangeY, m_mapInfo.mapSize.x);
        CalcDrawRange(static_cast<int>(player->AccessPos().NowX()) / m_mapInfo.tileSize.y, rangeX, m_mapInfo.mapSize.y);

        for (size_t i = rangeY.first; i <= rangeY.second; i++)
        {
            for (size_t j = rangeX.first; j <= rangeX.second; j++)
            {
                // チャンクに沿ったキーを生成
                auto key = (static_cast<uint64_t>(i / m_mapInfo.chunkSize.y) << 32) | static_cast<uint64_t>(j / m_mapInfo.chunkSize.x);

                // ローカルインデックスでタイル取得
                const size_t localY = i % m_mapInfo.chunkSize.y;
                const size_t localX = j % m_mapInfo.chunkSize.x;
                const size_t localIndex = localY * m_mapInfo.chunkSize.x + localX;

                // 座標に沿ったハンドル取得
                auto mapIt = m_mapData.find(key);
                if (mapIt == m_mapData.end()) continue;
                int handle = AppCtx::AssetMgr().Fetch<asset::DivisionGraph>()->GetHandle("map", mapIt->second.at(localIndex));

                // チャンクに沿った座標に描画
                int x = static_cast<int>(j * m_mapInfo.tileSize.x);
                int y = static_cast<int>(i * m_mapInfo.tileSize.y);
                DrawGraph(x, y, handle, true);
            }
        }
    }

    void Map::CalcDrawRange(int pos, std::pair<size_t, size_t>& range, size_t length)
    {
        // 範囲算出
        if (length == 0) { range = {0, 0}; return; }
        const int maxIndex = static_cast<int>(length) - 1;
        range.first  = static_cast<size_t>(std::clamp(pos - 5, 0, maxIndex));
        range.second = static_cast<size_t>(std::clamp(pos + 5, 0, maxIndex));
    }
}
