#pragma once
#include<json.hpp>
#include<unordered_map>
#include<memory>
#include<array>
#include<typeindex>
#include"CollisionBase/CollisionBase.h"

using json = nlohmann::json;

namespace object
{
    class GameObject;
}

/// <summary>
/// 当たり判定関連
/// </summary>
namespace collision
{
    /// <summary>
    /// 当たり判定情報を管理する
    /// </summary>
    class CollisionManager final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        CollisionManager() = default;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_owner">所有者</param>
        CollisionManager(object::GameObject* _owner);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~CollisionManager();

        /// <summary>
        /// 当たり判定追加
        /// </summary>
        /// <typeparam name="T">当たり判定名</typeparam>
        /// <typeparam name="...Args">引数群</typeparam>
        /// <param name="...args">引数群</param>
        /// <returns>追加した当たり判定</returns>
        template<typename T, typename... Args>
        std::shared_ptr<T> AddCollision(Args&&... args)
        {
            auto collision = std::make_shared<T>(std::forward<Args>(args)...);
            collisions.push_back(collision);
            return collision;
        }

        /// <summary>
        /// 当たり判定取得
        /// </summary>
        /// <typeparam name="T">取得したい当たり判定</typeparam>
        /// <returns>当たり判定</returns>
        std::shared_ptr<CollisionBase> GetCollision(uint64_t _shape)
        {
            for (auto& collision : collisions)
            {
                if (_shape == static_cast<uint64_t>(collision->MyShape()))
                {
                    return collision;
                }
            }
            return nullptr;
        }

        /// <summary>
        /// 組み合わせ毎当たり判定実施
        /// </summary>
        void ColliderWith();

    private:
        std::vector<std::shared_ptr<CollisionBase>> collisions;     //当たり判定群
    };

    static std::unordered_map<object::GameObject*, CollisionManager*> allCollision;     //全当たり判定
}
