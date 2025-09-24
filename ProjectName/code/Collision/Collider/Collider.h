#pragma once
#include <memory>
#include "math/Vector2.h"
#include "ColliderFilter.h"
#include <functional>

using namespace math;

/// <summary>
/// 当たり判定関連
/// </summary>
namespace col2d
{
    struct ColliderDef;
    class ColliderVisitor;

    struct ContactListener
    {
        std::function<bool()> when; // 条件
        std::function<void()> event; // 処理
    };

    /// <summary>
    /// コライダー
    /// </summary>
    /// <remarks>
    /// 当たり判定を行うための機能を所持する
    /// </remarks>
    class Collider
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_def">コライダー定義</param>
        Collider(ColliderDef* _def)
            : filter()
            , velocity()
        {
            colDef = std::make_unique<ColliderDef>(*_def);
        }

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~Collider() {};

        /// <summary>
        /// カテゴリーの生成
        /// </summary>
        /// <param name="_ownerID">所有者のID</param>
        virtual void GenerateCategory(uint32_t _ownerID = 0) = 0;

        /// <summary>
        /// コライダーの定義情報を取得
        /// </summary>
        /// <returns>コライダー定義情報へのポインタ</returns>
        ColliderDef* GetColliderDef() const
        {
            return colDef.get();
        }

        /// <summary>
        /// ビジターの受け入れ
        /// </summary>
        /// /// <param name="_visitor">他のコライダー</param>
        virtual void Accept(ColliderVisitor& _visitor) = 0;

        /// <summary>
        /// 衝突判定
        /// </summary>
        /// <param name="_other">他のコライダー</param>
        virtual void ColliderWidth(Collider& _other) = 0;

        /// <summary>
        /// コライダーのフィルタ情報を取得
        /// </summary>
        Filter& GetFilter()
        {
            return filter;
        }

        /// <summary>
        /// 移動量の設定
        /// </summary>
        void SetVelocity(const Vector2f& _velocity)
        {
            velocity = _velocity;
        }

        /// <summary>
        /// 移動量の取得
        /// </summary>
        /// <returns>移動量</returns>
        Vector2f GetVelocity() const
        {
            return velocity;
        }

        /// <summary>
        /// イベントの追加
        /// </summary>
        /// <param name="_key">イベントのキー</param>
        /// <param name="_event">追加するイベント</param>
        void AddEvent(const uint64_t& _key, const ContactListener& _event)
        {
            events[_key].push_back(_event);
        }

        /// <summary>
        /// イベントの発火
        /// </summary>
        /// <param name="_key">イベントのキー</param>
        void TriggerEvent(const uint64_t& _key)
        {
            if (events.contains(_key))
            {
                for (auto& event : events[_key])
                {
                    if (event.when())
                    {
                        event.event();
                    }
                }
            }
        }

    protected:
        /// <summary>
        /// 移動量の追加
        /// </summary>
        /// <param name="_velocity">移動量</param>
        virtual void AddVelocity(const Vector2f& _velocity) {};

        Filter filter; // コライダーのフィルタ情報
        std::unique_ptr<ColliderDef> colDef; // コライダーの定義情報へのポインタ
        Vector2f velocity; // 速度
        std::unordered_map<uint64_t, std::vector<ContactListener>> events; // 接触イベントリスト
    };
}
