module;
#include <thread>
#include <fstream>
#include <json.hpp>

module Collider.TileCollider;

import <algorithm>;

import MyLib.Math.Vector2;
import Collider.RectCollider;
import MyLib.FileIO.MemMapFile;
import MyLib.FileIO.ExeFilePath;
import GameSystem.Window;
import Collider.TileColliderVisitor;

using namespace math;

namespace col2d
{
    TileCollider::TileCollider(ColliderDef* def)
        :Collider(def)
    {
        m_visitor = std::make_unique<TileColliderVisitor>(*this);
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
        m_tileSize = { info["tilewidth"], info["tileheight"] };

        auto path = file::GetExeDirectory() / "data/MapTip.csv";
        file::MemMapFile mmf;
        mmf.Open(path.string().c_str());
        char* filePtr = mmf.GetPtr();
        char* fileEnd = filePtr + mmf.GetFileSize();

        // 1チャンクはウィンドウサイズ4つ分
        m_chunkSize = gameSystem::Window::Instance().GetWindowData()->SIZE / m_tileSize.Half();

        std::vector<size_t> mapData;
        mapData.reserve(mapInfo.width * mapInfo.height);
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
                uint32_t chunkY = static_cast<uint32_t>(y / m_chunkSize.y);
                uint32_t chunkX = static_cast<uint32_t>(x / m_chunkSize.x);
                size_t key = MakeTileKey(chunkX, chunkY);

                // キーに対して要素がなければ初期化としてメモリ確保
                if (auto it = m_tileColliders.find(key); it == m_tileColliders.end())
                {
                    m_tileColliders.emplace(key, std::vector<TileInfo>(m_chunkSize.x * m_chunkSize.y));
                    
                }

                // タイルコライダーを生成
                TileInfo tileInfo;
                tileInfo.adjacentFlag = adjacentFlag;
                ColliderDef colDef = {};
                colDef.localPos = Vector2f(static_cast<float>(x * m_tileSize.x), static_cast<float>(y * m_tileSize.y));
                colDef.isActive = true;
                tileInfo.collider = std::make_unique<RectCollider>(&colDef);
                tileInfo.collider->Initialize(static_cast<float>(m_tileSize.x), static_cast<float>(m_tileSize.y));

                // コライダーをチャンク内の座標に格納
                const size_t colIndex = (y % m_chunkSize.y) * m_chunkSize.x + (x % m_chunkSize.x);
                m_tileColliders[key][colIndex] = std::move(tileInfo);
            }
        }
    }

    bool TileCollider::IsColliding(const shape::Rect& rect)
    {
        while(!m_hitTileKeys.empty())
        {
            m_hitTileKeys.pop();
        }

        // タイル範囲を計算
        Vector2f tileLeft = rect.pos / m_tileSize;
        tileLeft.x = std::floor(tileLeft.x);
        tileLeft.y = std::floor(tileLeft.y);
        Vector2f tileRight = (rect.pos + rect.size) / m_tileSize;
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
        chunkLeft.x = static_cast<uint32_t>(std::floor(tileLeft.x / m_chunkSize.x));
        chunkLeft.y = static_cast<uint32_t>(std::floor(tileLeft.y / m_chunkSize.y));
        Vector2u chunkRight{};
        chunkRight.x = static_cast<uint32_t>(std::floor(tileRight.x / m_chunkSize.x));
        chunkRight.y = static_cast<uint32_t>(std::floor(tileRight.y / m_chunkSize.y));

        // チャンク内のタイルコライダーを走査
        for (uint32_t cy = chunkLeft.y; cy <= chunkRight.y; ++cy)
        {
            for (uint32_t cx = chunkLeft.x; cx <= chunkRight.x; ++cx)
            {
                // チャンクのキーを生成
                size_t key = MakeTileKey(cx, cy);

                // チャンクのタイルコライダーを取得
                auto iter = m_tileColliders.find(key);
                if (iter == m_tileColliders.end())
                {
                    continue;
                }

                // チャンク内のタイル範囲を計算
                Vector2<size_t> localLeft{};
                localLeft.x = (cx == chunkLeft.x) ? Mod(static_cast<size_t>(tileLeft.x), m_chunkSize.x) : 0;
                localLeft.y = (cy == chunkLeft.y) ? Mod(static_cast<size_t>(tileLeft.y), m_chunkSize.y) : 0;
                Vector2<size_t> localRight{};
                localRight.x = (cx == chunkRight.x) ? Mod(static_cast<size_t>(tileRight.x), m_chunkSize.x) : (m_chunkSize.x - 1);
                localRight.y = (cy == chunkRight.y) ? Mod(static_cast<size_t>(tileRight.y), m_chunkSize.y) : (m_chunkSize.y - 1);

                // チャンク内のタイル範囲を走査
                for (size_t ty = localLeft.y; ty <= localRight.y; ++ty)
                {
                    for (size_t tx = localLeft.x; tx <= localRight.x; ++tx)
                    {
                        // タイルのインデックスを生成
                        size_t index = ty * m_chunkSize.x + tx;

                        // タイルコライダーが存在するか確認
                        if (index >= iter->second.size() || !iter->second[index].collider)
                        {
                            continue;
                        }
                        
                        if (iter->second[index].collider->GetRect().AABB(rect))
                        {
                            m_hitTileKeys.push({ key, index });
                        }
                    }
                }
            }
        }

        // 範囲内にタイルコライダーが存在する場合はtrueを返す
        if (!m_hitTileKeys.empty())
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
