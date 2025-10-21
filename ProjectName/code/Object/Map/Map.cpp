module;
#include <DxLib.h>
#include <fstream>
#include <functional>


module Object.Map;

import <json.hpp>;

import MyLib.FileIO.MemMapFile;
import MyLib.Loading.LoadingContext;
import Asset.DivisionGraph;

namespace object
{
    Map::Map()
        : filePtr()
        , player()
    {
        //マップ構成読み込み
        task::LoadingContext::Get()->AddTask(task::DATA, [this]() {
            file::MemMapFile mmf;
            auto path = file::GetExeDirectory() / "data/MapTip.csv";
            mmf.Open(path.string().c_str());
            filePtr = mmf.GetPtr();

            //マップデータの作成
            CreateMapData(filePtr);
        });

        //タイル情報読み込み
        task::LoadingContext::Get()->AddTask(task::DATA, [this]() {
            auto jpath = file::GetExeDirectory() / "data/MapData.json";
            std::ifstream ifs(jpath.string());
            ifs >> mapInfo;
            ifs.close();
        });

        //マップ画像読み込み
        m_assetMgr->Load<asset::DivisionGraph>("map", "map.png", 32, 32);

    }

    void Map::Init()
    {
        col2d::ColliderDef def;
        def.isActive = true;
        auto id = ObjectContext::ColMgr().CreateTileCollider(&def, MyObjectTag());
        ObjectContext::ColMgr().AddMask(id, col2d::RECT, PLAYER);
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
            CalcDrawRange(static_cast<int>(player->AccessPos().NowX()) / width, rangeX, mapData.at(i).size() - 1);
            for (size_t j = rangeX.first; j <= rangeX.second; j++)
            {
                int handle = m_assetMgr->Fetch<asset::DivisionGraph>()->GetHandle("map", mapData.at(i).at(j));
                DrawGraph(static_cast<int>(width * j), static_cast<int>(height * i), handle, true);
            }
        }
    }

    void Map::CalcDrawRange(int pos, std::pair<size_t, size_t>& range, size_t length)
    {
        range.first = std::clamp<int>(pos - 5, 0, (int)length);
        range.second = std::clamp<int>(pos + 5, 0, (int)length);
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
