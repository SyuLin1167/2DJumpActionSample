#pragma once

namespace object
{
    class GameObject;
}

/// <summary>
/// コンポーネント関連
/// </summary>
namespace component
{
    /// <summary>
    /// コンポーネントの基底クラス
    /// </summary>
    class ComponentBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        ComponentBase() = default;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="owner">所有者</param>
        /// <param name="order">更新順番</param>
        explicit ComponentBase(class object::GameObject* owner);

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~ComponentBase() = default;

        /// <summary>
        /// 更新
        /// </summary>
        /// <param name="deltaTime">デルタタイム</param>
        virtual void Update(const float& deltaTime) {};

    protected:
        class object::GameObject* owner;  //所有者
    };
}
