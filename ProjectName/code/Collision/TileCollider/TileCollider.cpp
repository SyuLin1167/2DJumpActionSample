#include "TileCollider.h"
#include <algorithm>
#include <thread>
#include <fstream>
#include "json.hpp"
#include "RectCollider/RectCollider.h"
#include "FileIO/ExeFilePath.h"
#include "FileIO/MemMapFile.h"

namespace col2d
{
    TileCollider::TileCollider(ColliderDef* _def)
        :Collider(_def)
        , visitor(*this)
    {
        Initialize();
    }

    void TileCollider::Initialize()
    {
        // マップデータの読み込み
        auto jpath = file::GetExeDirectory() / "data/MapData.json";
        std::ifstream ifs(jpath.string());
        nlohmann::json info;
        ifs >> info;
        mapInfo.width = info["width"];
        mapInfo.height = info["height"];
        ifs.close();
        tileSize = { info["tilewidth"], info["tileheight"] };

        auto path = file::GetExeDirectory() / "data/MapTip.csv";
        file::MemMapFile mmf;
        mmf.Open(path.string().c_str());
        char* filePtr = mmf.GetPtr();
        char* fileEnd = filePtr + mmf.GetFileSize();

        // 1チャンクはウィンドウサイズ4つ分
        chunkSize = gameSystem::Window::GetWindowData()->SIZE / tileSize.Half();

        std::vector<size_t> mapData;
        while (filePtr < fileEnd)
        {
            // 空白、カンマ、改行をスキップ
            if (*filePtr == ' ' || *filePtr == ',' || *filePtr == '\r' || *filePtr == '\n')
            {
                ++filePtr;
                continue;
            }

            // 数字を読み込み
            if (*filePtr >= '0' && *filePtr <= '9')
            {
                size_t tileID = 0;

                // 数字を連続して読み込む
                while (filePtr < fileEnd && *filePtr >= '0' && *filePtr <= '9')
                {
                    tileID = tileID * 10 + (*filePtr - '0');
                    ++filePtr;
                }
                mapData.push_back(tileID);
                continue;
            }

            // 不明な文字はスキップ
            ++filePtr;
        }

        for (size_t y = 0; y < mapInfo.height; ++y)
        {
            for (size_t x = 0; x < mapInfo.width; ++x)
            {
                const size_t tileIndex = y * mapInfo.width + x;

                // タイルが存在しない場合はスキップ
                if (mapData[tileIndex] == 0)
                {
                    continue;
                }

                // 隣接するタイルがすべて存在する場合はスキップ
                auto adjacentFlag = AdjacentTileAt(mapData, x, y);
                if (adjacentFlag == TileFlag::ALL)
                {
                    continue;
                }

                // チャンクの算出とそれに伴うキーの生成
                uint32_t chunkY = static_cast<uint32_t>(y / chunkSize.y);
                uint32_t chunkX = static_cast<uint32_t>(x / chunkSize.x);
                size_t key = MakeTileKey(chunkX, chunkY);

                // キーに対して要素がなければ初期化としてメモリ確保
                if (!tileColliders.contains(key))
                {
                    tileColliders[key].resize(chunkSize.x * chunkSize.y);
                }

                // タイルコライダーを生成
                TileInfo tileInfo;
                tileInfo.adjacentFlag = adjacentFlag;
                ColliderDef colDef = {};
                colDef.localPos = Vector2f(x * tileSize.x, y * tileSize.y);
                colDef.isActive = true;
                tileInfo.collider = std::make_unique<RectCollider>(&colDef);
                tileInfo.collider->Initialize(tileSize.x, tileSize.y);

                // コライダーをチャンク内の座標に格納
                const size_t colIndex = y % (chunkSize.y) * chunkSize.x + x % (chunkSize.x);
                tileColliders[key][colIndex] = std::move(tileInfo);
            }
        }
    }

    bool TileCollider::IsColliding(const shape::Rect& _rect)
    {
        while(!hitTileKeys.empty())
        {
            hitTileKeys.pop();
        }

        // タイル範囲を計算
        Vector2f tileLeft = _rect.pos / tileSize;
        tileLeft.x = std::floor(tileLeft.x);
        tileLeft.y = std::floor(tileLeft.y);
        Vector2f tileRight = (_rect.pos + _rect.size) / tileSize;
        tileRight.x = std::ceil(tileRight.x) - 1;
        tileRight.y = std::ceil(tileRight.y) - 1;

        // タイル範囲が無効な場合はfalseを返す
        if (tileLeft.x > tileRight.x || tileLeft.y > tileRight.y)
        {
            return false;
        }

        if (tileRight.x < 0 || tileRight.y < 0 || tileLeft.x >= mapInfo.width || tileLeft.y >= mapInfo.height)
        {
            return false;
        }

        // チャンク範囲を計算
        Vector2u chunkLeft{};
        chunkLeft.x = std::floor(tileLeft.x / chunkSize.x);
        chunkLeft.y = std::floor(tileLeft.y / chunkSize.y);
        Vector2u chunkRight{};
        chunkRight.x = std::floor(tileRight.x / chunkSize.x);
        chunkRight.y = std::floor(tileRight.y / chunkSize.y);

        // チャンク内のタイルコライダーを走査
        for (uint32_t cy = chunkLeft.y; cy <= chunkRight.y; ++cy)
        {
            for (uint32_t cx = chunkLeft.x; cx <= chunkRight.x; ++cx)
            {
                // チャンクのキーを生成
                size_t key = MakeTileKey(cx, cy);

                // チャンクのタイルコライダーを取得
                auto iter = tileColliders.find(key);
                if (iter == tileColliders.end())
                {
                    continue;
                }

                // チャンク内のタイル範囲を計算
                Vector2<size_t> localLeft{};
                localLeft.x = (cx == chunkLeft.x) ? Mod(tileLeft.x, chunkSize.x) : 0;
                localLeft.y = (cy == chunkLeft.y) ? Mod(tileLeft.y, chunkSize.y) : 0;
                Vector2<size_t> localRight{};
                localRight.x = (cx == chunkRight.x) ? Mod(tileRight.x, chunkSize.x) : (chunkSize.x - 1);
                localRight.y = (cy == chunkRight.y) ? Mod(tileRight.y, chunkSize.y) : (chunkSize.y - 1);

                // チャンク内のタイル範囲を走査
                for (size_t ty = localLeft.y; ty <= localRight.y; ++ty)
                {
                    for (size_t tx = localLeft.x; tx <= localRight.x; ++tx)
                    {
                        // タイルのインデックスを生成
                        size_t index = ty * chunkSize.x + tx;

                        // タイルコライダーが存在するか確認
                        if (index >= iter->second.size() || !iter->second[index].collider)
                        {
                            continue;
                        }
                        
                        if (iter->second[index].collider->GetRect().AABB(_rect))
                        {
                            hitTileKeys.push({ key, index });
                        }
                    }
                }
            }
        }

        // 範囲内にタイルコライダーが存在する場合はtrueを返す
        if (!hitTileKeys.empty())
        {
            return true;
        }

        // 範囲内にタイルコライダーが存在しない場合はfalseを返す
        return false;
    }

    uint8_t TileCollider::AdjacentTileAt(const std::vector<size_t>& _mapData, size_t _x, size_t _y) const
    {
        uint8_t flag = 0;
        const size_t tileIndex = _y * mapInfo.width + _x;

        // 左のタイルが存在するか
        if (_x > 0 && _mapData[tileIndex - 1] != 0)
        {
            flag |= TileFlag::LEFT;
        }
        // 右のタイルが存在するか
        if (_x < mapInfo.width - 1 && _mapData[tileIndex + 1] != 0)
        {
            flag |= TileFlag::RIGHT;
        }
        // 上のタイルが存在するか
        if (_y > 0 && _mapData[tileIndex - mapInfo.width] != 0)
        {
            flag |= TileFlag::TOP;
        }
        // 下のタイルが存在するか
        if (_y < mapInfo.height - 1 && _mapData[tileIndex + mapInfo.width] != 0)
        {
            flag |= TileFlag::BOTTOM;
        }
        return flag;
    }
}
