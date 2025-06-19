#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>

/// <summary>
/// コンポーネント関連
/// </summary>
namespace component
{
    class ComponentBase;

    /// <summary>
    /// コンポーネントを管理する
    /// </summary>
    class ComponentManager final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        ComponentManager() = default;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~ComponentManager() = default;

        /// <summary>
        /// 更新処理
        /// </summary>
        /// <param name="_deltaTime">デルタタイム</param>
        void Update(const float& _deltaTime);

        /// <summary>
        /// コンポーネント追加
        /// </summary>
        /// <typeparam name="T">コンポーネント名</typeparam>
        /// <typeparam name="...Args">引数群</typeparam>
        /// <param name="...args">引数群</param>
        /// <returns>追加したコンポーネント</returns>
        template<typename T, typename... Args>
        std::shared_ptr<T> AddComponent(Args&&... _args)
        {
            auto component = std::make_shared<T>(std::forward<Args>(_args)...);
            components[typeid(T)] = component;
            return component;
        }

        /// <summary>
        /// コンポーネントの取得
        /// </summary>
        /// <typeparam name="T">取得対象のコンポーネント名</typeparam>
        /// <returns>コンポーネント</returns>
        template<typename T>
        std::shared_ptr<T> GetComponent()
        {
            if (HasComponent<T>())
            {
                return std::dynamic_pointer_cast<T>(components[typeid(T)]);
            }
            return nullptr;
        }

        /// <summary>
        /// コンポーネントの存在確認
        /// </summary>
        /// <typeparam name="T">確認対象のコンポーネント</typeparam>
        /// <returns>存在するかどうか</returns>
        template<typename T>
        bool HasComponent()
        {
            return components.find(typeid(T)) != components.end();
        }

        /// <summary>
        /// コンポーネント削除
        /// </summary>
        /// <param name="component">削除するコンポーネント</param>
        template<typename T>
        void RemoveComponent()
        {
            components.erase(typeid(T));
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<component::ComponentBase>> components;   //コンポーネント群
    };
}
