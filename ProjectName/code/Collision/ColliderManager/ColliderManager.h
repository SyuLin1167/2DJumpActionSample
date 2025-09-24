#pragma once
#include <queue>
#include <unordered_map>
#include <memory>
#include <RectCollider/RectCollider.h>
#include <TileCollider/TileCollider.h>
#include <functional>

/// <summary>
/// 当たり判定関連
/// </summary>
namespace col2d
{
    struct ColliderDef;
    class Collider;

    /// <summary>
    /// コライダーの識別子
    /// </summary>
    struct ColliderID
    {
        uint32_t index;          // コライダーのインデックス
        uint16_t generation;     // コライダーの生成世代
    };

    /// <summary>
    /// コライダー管理
    /// </summary>
    class ColliderManager
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
        /// <param name="_def">コライダー定義</param>
        /// <param name="_args">コライダー生成時に渡す引数</param>
        /// <returns>生成されたコライダーの識別子</returns>
        template<typename T, typename... Args>
        inline ColliderID CreateCollider(ColliderDef* _def, const uint32_t& _ownerID, Args&&... _args)
        {
            ColliderID cID = CreateID();
            auto col = std::make_unique<T>(_def);
            col->GenerateCategory(_ownerID);
            col->Initialize(std::forward<Args>(_args)...);
            colliders[cID.index] = std::move(col);
            return cID;
        }

        /// <summary>
        /// 矩形コライダーを生成
        /// </summary>
        /// <param name="_def">コライダー定義</param>
        /// <param name="_size">サイズ</param>
        /// <returns>生成されたコライダーの識別子</returns>
        ColliderID CreateRectCollider(ColliderDef* _def, const Vector2f& _size, const uint32_t& _ownerID = 0)
        {
            return CreateCollider<RectCollider>(_def, _ownerID, _size);
        }

        /// <summary>
        /// タイルコライダーを生成
        /// </summary>
        /// <param name="_def">コライダー定義</param>
        /// <returns>生成されたコライダーの識別子</returns>
        ColliderID CreateTileCollider(ColliderDef* _def, const uint32_t& _ownerID = 0)
        {
            return CreateCollider<TileCollider>(_def, _ownerID);
        }

        /// <summary>
        /// コライダーを削除
        /// </summary>
        /// <param name="_cID">コライダーの識別子</param>
        void DestroyCollider(const ColliderID& _cID);

        /// <summary>
        /// コライダーを取得
        /// </summary>
        /// <param name="_cID">コライダーの識別子</param>
        /// <returns>コライダーへのポインタ</returns>
        Collider* GetCollider(const ColliderID& _cID) const
        {
            if (colliders.contains(_cID.index))
            {
                return colliders.at(_cID.index).get();
            }
            return nullptr;
        }

        /// <summary>
        /// コライダーの更新処理
        /// </summary>
        void Step();

        /// <summary>
        /// マスクを追加
        /// </summary>
        /// <param name="_cID">コライダーの識別子</param>
        /// <param name="_shape">形状の種類</param>
        /// <param name="_ownerID">所有者のID</param>
        void AddMask(const ColliderID& _cID, const uint32_t& _shape, const uint32_t& _ownerID)
        {
            if (colliders.contains(_cID.index))
            {
                colliders.at(_cID.index)->GetFilter().AddMask(_shape, _ownerID);
            }
        }

        void AddEvent(const ColliderID& _cID, const uint64_t& _key, ContactListener _event)
        {
            if (colliders.contains(_cID.index))
            {
                colliders.at(_cID.index)->AddEvent(_key, std::move(_event));
            }
        }

    private:
        /// <summary>
        /// コライダーの識別子を生成
        /// </summary>
        /// <returns>生成されたコライダーの識別子</returns>
        ColliderID CreateID();

        std::queue<uint32_t> freeIndex; // 使用されていないコライダーのインデックス
        std::unordered_map<uint64_t, std::unique_ptr<Collider>> colliders; // コライダーのマップ
    };
}
