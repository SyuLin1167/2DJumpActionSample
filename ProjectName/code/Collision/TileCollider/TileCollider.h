#pragma once
#include <unordered_map>
#include <queue>
#include "Collider/Collider.h"

#include "TileColliderVisitor.h"
#include "Window/Window.h"

/// <summary>
/// 当たり判定関連
/// </summary>
namespace col2d
{
    /// <summary>
    /// タイルの隣接フラグ
    /// </summary>
    enum TileFlag : uint8_t
    {
        NONE = 0,           // なし
        LEFT = 1 << 1,      // 左側
        RIGHT = 1 << 2,     // 右側
        TOP = 1 << 3,       // 上側
        BOTTOM = 1 << 4,    // 下側
        ALL = (1 << 4) - 1  // 全方向
    };

    /// <summary>
    /// タイルコライダー
    /// </summary>
    /// <remarks>
    /// タイルマップのタイルに対するコライダー
    /// </remarks>
    class TileCollider final :public Collider
    {
        struct TileInfo; // タイル情報の前方宣言
    public:

        /// <summary>
        /// コンストラクタ
        /// </summary>
        TileCollider(ColliderDef* _def);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~TileCollider() override = default;

        /// <summary>
        /// カテゴリーの生成
        /// </summary>
        /// <param name="_ownerID">所有者のID</param>
        void GenerateCategory(uint32_t _ownerID = 0) override
        {
            filter.category = MakeKey(ShapeType::TILE, _ownerID);
        }

        /// <summary>
        /// 初期化
        /// </summary>
        void Initialize();

        /// <summary>
        /// タイルコライダーの衝突判定
        /// </summary>
        /// <param name="_rect">矩形</param>
        /// <returns>衝突しているか</returns>
        bool IsColliding(const shape::Rect& _rect);

        /// <summary>
        /// 他のコライダーとの衝突判定
        /// </summary>
        /// <param name="_other">他のコライダー</param>
        void ColliderWidth(Collider& _other) override
        {
            _other.Accept(visitor);
        }

        /// <summary>
        /// ヒットしたタイルのキーを取得
        /// </summary>
        /// <returns>ヒットしたタイルのキー/returns>
        std::queue<std::pair<size_t, size_t>> GetHitTileKeys() const
        {
            return std::move(hitTileKeys);
        }

        /// <summary>
        /// タイル情報を取得
        /// </summary>
        /// <param name="_key">タイルのキー</param>
        /// <param name="_index">タイルのインデックス</param>
        /// <returns>タイル情報へのポインタ</returns>
        inline const TileInfo* GetTileInfo(size_t _key, size_t _index) const
        {
            if (tileColliders.contains(_key) && _index < tileColliders.at(_key).size())
            {
                return &tileColliders.at(_key)[_index];
            }
            return nullptr;
        }

        const Vector2u& GetTileSize() const
        {
            return tileSize;
        }

    private:
        /// <summary>
        /// タイルのキーを生成
        /// </summary>
        /// <param name="cx">チャンクのX座標</param>
        /// <param name="cy">チャンクのY座標</param>
        /// <returns>生成されたキー</returns>
        static inline uint64_t MakeTileKey(uint32_t cx, uint32_t cy)
        {
            return (static_cast<uint64_t>(cy) << 32) | static_cast<uint64_t>(cx);
        }

        /// <summary>
        /// 値を指定の範囲で剰余演算
        /// </summary>
        /// <param name="value">値</param>
        /// <param name="mod">剰余の値</param>
        /// <returns>剰余演算の結果</returns>
        static inline size_t Mod(size_t value, size_t mod)
        {
            return value % mod;
        }

        /// <summary>
        /// 隣接するタイルのフラグを取得
        /// <summary>
        /// <param name="_tileLayer">タイルレイヤー</param>
        /// <param name="_x">タイルのX座標</param>
        /// <param name="_y">タイルのY座標</param>
        uint8_t AdjacentTileAt(const std::vector<size_t>& _mapData,size_t _x, size_t _y) const;


        /// <summary>
        /// コライダーを訪問
        /// </summary>
        /// <param name="_visitor">訪問するビジター</param>
        void Accept(ColliderVisitor& _visitor) override {}

        struct MapInfo
        {
            size_t width;      // マップの幅（タイル数）
            size_t height;     // マップの高さ（タイル数）
        }mapInfo;

        Vector2u chunkSize; // チャンクサイズ
        Vector2u tileSize; // タイルのサイズ
        TileColliderVisitor visitor; // タイルコライダービジター

        /// <summary>
        /// タイル情報
        /// summary>
        struct TileInfo
        {
            uint8_t adjacentFlag; // 隣接するタイルのフラグ
            std::unique_ptr<RectCollider> collider; // タイルに対応する矩形コライダー
        };

        std::unordered_map<size_t, std::vector<TileInfo>> tileColliders; // タイル状のコライダーを保持するベクター
        std::queue<std::pair<size_t, size_t>> hitTileKeys; // ヒットしたタイルのキー
    };
}

