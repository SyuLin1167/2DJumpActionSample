#include <algorithm>
#include <fstream>
#include <format>
#include <json.hpp>
#include "MapCollision.h"
#include "FileIO/MemMapFile.h"
#include "Loading/LoadingContext.h"
#include "RectCollision/RectCollision.h"
#include "TipBox/NomalBox/NomalBox.h"

using json = nlohmann::json;

namespace collision
{
    MapCollision::MapCollision(std::string _fileName)
        :boxFlag()
    {
        //マップチップデータ読み込み&作成
        task::LoadingContext::Get()->AddTask(task::DATA, [_fileName, this]() {
            auto path = file::GetExeDirectory() / std::format("data/{}.csv", _fileName);
            file::MemMapFile mmf;
            mmf.Open(path.string().c_str());
            char* ptr = nullptr;
            mmf.GetPtr((void**)&ptr);
            CreateMapData(ptr);
        });

        //タイル情報読み込み
        task::LoadingContext::Get()->AddTask(task::DATA, [this]() {
            json data;
            auto jpath = file::GetExeDirectory() / "data/MapData.json";
            std::ifstream ifs(jpath.string());
            ifs >> data;
            ifs.close();
            colRect.size.x = data["tilewidth"];
            colRect.size.y = data["tileheight"];
        });
    }

    void MapCollision::ColliderWith(RectCollision& _other, TargetColInfo& _info)
    {
        HandlingCollision(_other, _info);
    }

    void MapCollision::HandlingCollision(RectCollision& _other, TargetColInfo& _info)
    {
        //Y軸の走査範囲
        auto swept = _other.SweptRect();
        rangeY.first = std::clamp((int)(swept.Top() / 32), 0, int(colData.size()));
        rangeY.second = std::clamp((int)(swept.Bottom() / 32), 0, int(colData.size()));
        int velY = _other.SignVelocity().y;

        //ブロック検索(Y軸)
        for (short y = rangeY.first; y <= rangeY.second; y++)
        {
            if (y < 0 || y >= colData.size())
            {
                continue;
            }

            //X軸の走査範囲
            rangeX.first = std::clamp((int)(swept.Left() / 32), 0, int(colData[y].size()));
            rangeX.second = std::clamp((int)(swept.Right() / 32), 0, int(colData[y].size()));

            //ブロック検索(X軸)
            for (short x = rangeX.first; x <= rangeX.second; x++)
            {
                if (x < 0 || x >= colData[y].size())
                {
                    continue;
                }

                //ブロックがあれば判定対象
                if (GetBlockInfo(x, y) == 0)
                {
                    colRect.pos = Vector2<float>(x, y) * colRect.size;
                    
                    //衝突していたら衝突時の処理を実施
                    if (_other.HasColliderRect(colRect))
                    {
                        SurveyAdjacentBlock(x, y);

                        //対象の矩形を元に当たり判定を生成
                        auto zeroVec = Vector2<float>(0, 0);
                        RectCollision tipBox = RectCollision(colRect, zeroVec);

                        //通常Boxの判定
                        NomalBox nomalBox = {};
                        nomalBox.ColliderWith(_other, tipBox, boxFlag);

                        //ジャンプ可能なら可能にする
                        if (velY > 0 && _other.SignVelocity().y == 0)
                        {
                            if (!_info.events.empty())
                            {
                                for (auto& event : _info.events)
                                {
                                    event();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void MapCollision::CreateMapData(char* ptr)
    {
        //マップデータを文字列から配列に変換して作成
        std::vector<size_t> row;
        for (char* p = ptr; *p != '\0'; p++)
        {
            if (*p == ',' || *p == '\r')
            {
                continue;
            }

            if (*p == '\n')
            {
                colData.emplace_back(row);
                row.clear();
            }
            else
            {
                row.emplace_back(size_t(*p - '0'));
            }
        }
    }

    void MapCollision::SurveyAdjacentBlock(size_t x, size_t y)
    {
        //隣接するブロックがあるか調査
        boxFlag = 0;
        if (GetBlockInfo(x - 1, y) == 0)
        {
            boxFlag |= LEFT;
        }
        if (GetBlockInfo(x + 1, y) == 0)
        {
            boxFlag |= RIGHT;
        }
        if (GetBlockInfo(x, y - 1) == 0)
        {
            boxFlag |= TOP;
        }
        if (GetBlockInfo(x, y + 1) == 0)
        {
            boxFlag |= BOTTOM;
        }
    }

    size_t MapCollision::GetBlockInfo(size_t x, size_t y)
    {
        //範囲外は判定なしを返す
        if (y < 0 || y >= colData.size())
        {
            return 1;
        }
        if (x < 0 || x >= colData[y].size())
        {
            return 1;
        }
        return colData[y][x];
    }
}
