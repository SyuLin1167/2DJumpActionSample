#include <DxLib.h>
#include <fstream>
#include <functional>
#include "Map.h"
#include "FileIO/MemMapFile.h"
#include "Loading/LoadingContext.h"
#include "DivisionGraph/DivisionGraph.h"
#include "MapCollision/MapCollision.h"

namespace object
{
    Map::Map()
        : filePtr()
        , player()
        , mmf(new file::MemMapFile)
    {
        //マップ構成読み込み
        task::LoadingContext::Get()->AddTask(task::DATA, [this]() {
            auto path = file::GetExeDirectory() / "data/MapTip.csv";
            mmf->Open(path.string().c_str());
            mmf->GetPtr((void**)&filePtr);
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
        });

        //タイル情報読み込み
        task::LoadingContext::Get()->AddTask(task::DATA, [this]() {
            auto jpath = file::GetExeDirectory() / "data/MapData.json";
            std::ifstream ifs(jpath.string());
            ifs >> mapInfo;
            ifs.close();
            std::this_thread::sleep_for(std::chrono::microseconds(5000));
        });

        //マップ画像読み込み
        assetMgr->Load<asset::DivisionGraph>("map", "map.png", 32, 32);

        //当たり判定追加
        colMgr->AddCollision<collision::MapCollision>("MapTip");
    }

    void Map::Init()
    {
        //マップデータの作成
        CreateMapData(filePtr);

    }

    void Map::GetReferenceObject(std::function<std::vector<std::shared_ptr<GameObject>>(uint32_t)> referenceObj)
    {
        //プレイヤー参照
        player = referenceObj(PLAYER).begin()->get();
    }

    void Map::Draw()
    {
        //描画範囲を算出して描画
        int width = mapInfo["tilewidth"];
        int height = mapInfo["tileheight"];
        CalcDrawRange(static_cast<int>(player->AccessPos().NowY()) / height, rangeY, mapData.size() - 1);
        for (size_t i = rangeY.first; i <= rangeY.second; i++)
        {
            CalcDrawRange(player->AccessPos().NowX() / width, rangeX, mapData[i].size() - 1);
            for (size_t j = rangeX.first; j <= rangeX.second; j++)
            {
                int handle = assetMgr->Fetch<asset::DivisionGraph>()->GetHandle("map", mapData[i][j]);
                DrawGraph(static_cast<int>(width * j), static_cast<int>(height * i), handle, true);
            }
        }
    }

    void Map::CalcDrawRange(int pos, std::pair<size_t, size_t>& range, size_t length)
    {
        range.first = std::clamp<int>(pos - 5, 0, length);
        range.second = std::clamp<int>(pos + 5, 0, length);
    }

    void Map::CreateMapData(char* ptr)
    {
        //マップデータ生成
        std::vector<size_t> row;
        for (char* p = ptr; *p != '\0'; p++)
        {
            if (*p != ',' && *p != '\r')
            {
                if (*p == '\n')
                {
                    mapData.emplace_back(row);
                    row.clear();
                }
                else
                {
                    row.emplace_back(int(*p - '0'));
                }
            }
        }
    }
}
