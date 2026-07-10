export module Collider.ColliderManager;

import <queue>;
import <memory>;
import <functional>;
import <unordered_map>;
import <string>;
import <future>;

import MyLib.Math.Vector2;
import Collider;
import Collider.RectCollider;
import Collider.TileCollider;
import Collider.CircleCollider;
import Object.MapInfo;

using namespace math;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{
    /// <summary>
    /// コライダーの識別子
    /// </summary>
    export struct ColliderID
    {
        uint32_t index;          // インデックス
        uint16_t generation;     // 生成世代
    };

    /// <summary>
    /// コライダー管理
    /// </summary>
    export class ColliderManager final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        ColliderManager() = default;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~ColliderManager() = default;

        /// <summary>
        /// コライダーを生成
        /// </summary>
        /// <typeparam name="T">コライダーの型</typeparam>
        /// <typeparam name="Args">コライダーの生成時に渡す引数の型</typeparam>
        /// <param name="def">コライダー定義</param>
        /// <param name="ownerID">所有者のID</param>
        /// <param name="args">コライダー生成時に渡す引数</param>
        /// <returns>生成されたコライダーの識別子</returns>
        template<typename T, typename... Args>
        [[nodiscard]] inline ColliderID CreateCollider(ColliderDef* def, const uint32_t& ownerID, Args&&... args)
        {
            ColliderID id = CreateID();
            auto col = std::make_unique<T>(def, std::forward<Args>(args)...);
            col->GenerateCategory(ownerID);
            m_colliders[id.index] = std::move(col);
            return id;
        }

        /// <summary>
        /// 矩形コライダーを生成
        /// </summary>
        /// <param name="def">コライダー定義</param>
        /// <param name="size">サイズ</param>
        /// <param name="ownerID">所有者のID</param>
        /// <returns>生成されたコライダーの識別子</returns>
        [[nodiscard]] inline ColliderID CreateRectCollider(ColliderDef* def, const Vector2f& size, const uint32_t& ownerID = 0)
        {
            return CreateCollider<RectCollider>(def, ownerID, size);
        }

        /// <summary>
        /// 円コライダーを生成
        /// </summary>
        /// <param name="def">コライダー定義</param>
        /// <param name="radius">半径</param>
        /// <param name="ownerID">所有者のID</param>
        /// <returns>生成されたコライダーの識別子</returns>
        [[nodiscard]] inline ColliderID CreateCircleCollider(ColliderDef* def, float radius, const uint32_t& ownerID = 0)
        {
            return CreateCollider<CircleCollider>(def, ownerID, radius);
        }

        /// <summary>
        /// タイルコライダーを生成
        /// </summary>
        /// <param name="def">コライダー定義</param>
        /// <param name="ownerID">所有者のID</param>
        /// <returns>生成されたコライダーの識別子</returns>
        [[nodiscard]] inline ColliderID CreateTileCollider(ColliderDef* def, const object::MapInfo& info, std::string fileName, const uint32_t& ownerID = 0)
        {
            return CreateCollider<TileCollider>(def, ownerID, info, fileName);
        }

        /// <summary>
        /// タイルコライダーを生成
        /// </summary>
        /// <param name="def">コライダー定義</param>
        /// <param name="ownerID">所有者のID</param>
        /// <returns>生成されたコライダーの識別子</returns>
        [[nodiscard]] inline ColliderID CreateTileCollider(ColliderDef* def, std::shared_future<object::MapInfo> info, std::string fileName, const uint32_t& ownerID = 0)
        {
            return CreateCollider<TileCollider>(def, ownerID, info, fileName);
        }

        /// <summary>
        /// コライダーを削除
        /// </summary>
        /// <param name="id">コライダーの識別子</param>
        void Destroy(const ColliderID& id);

        /// <summary>
        /// コライダーを取得
        /// </summary>
        /// <param name="id">コライダーの識別子</param>
        /// <returns>コライダーへのポインタ</returns>
        Collider* GetCollider(const ColliderID& id) const;

        /// <summary>
        /// コライダーの更新処理
        /// </summary>
        void Step();

        /// <summary>
        /// マスクを追加
        /// </summary>
        /// <param name="id">コライダーの識別子</param>
        /// <param name="shape">形状の種類</param>
        /// <param name="ownerID">所有者のID</param>
        void AddMask(const ColliderID& id, const uint32_t& shape, const uint32_t& ownerID)
        {
            if (auto it = m_colliders.find(id.index); it != m_colliders.end()) {
                it->second->GetFilter().AddMask(shape, ownerID);
            }
        }

        /// <summary>
        /// 衝突時イベントを追加
        /// </summary>
        /// <param name="id">コライダーの識別子</param>
        /// <param name="key">対象のイベントを識別するためのキー</param>
        /// <param name="event">追加するイベント</param>
        void AddEvent(const ColliderID& id, const uint64_t& key, ContactListener event)
        {
            if (auto it = m_colliders.find(id.index); it != m_colliders.end()) {
                it->second->AddEvent(key, event);
            }
        }

    private:
        /// <summary>
        /// コライダーの識別子を生成
        /// </summary>
        /// <returns>生成されたコライダーの識別子</returns>
        ColliderID CreateID();

        std::queue<ColliderID> m_freeID; // 未使用のコライダーID
        std::unordered_map<uint32_t, uint16_t> m_generations; // 現在の世代を管理
        std::unordered_map<uint32_t, std::unique_ptr<Collider>> m_colliders; // コライダーのマップ
    };
}
