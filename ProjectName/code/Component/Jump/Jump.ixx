module;
#include <functional>

export module Component.Jump;

import Component;

/// <summary>
/// コンポーネント関連
/// </summary>
export namespace component
{
    constexpr float GRAVITY = 3.8f;         //重力加速度
    constexpr float FALL_SPEED = 5.0f;      //落下速度
    constexpr float JUMP_POWER = -8.0f;    //ジャンプ力

    /// <summary>
    /// ジャンプ処理
    /// </summary>
    export class Jump final :public ComponentBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Jump() = default;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="owner">所有者</param>
        /// <param name="trigger">更新の優先順位</param>
        Jump(object::GameObject* owner, std::function<bool()> trigger);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Jump() = default;

        /// <summary>
        /// 更新
        /// </summary>
        /// <param name="deltaTime">デルタタイム</param>
        void Update(const float& deltaTime) override;

        /// <summary>
        /// ジャンプの実行
        /// </summary>
        void TryJump();

        /// <summary>
        /// ジャンプ可能にする
        /// </summary>
        void CanJump()
        {
            m_nowJump = false;
        }

    private:
        static constexpr float MAX_FALL_VELOCITY = 30.0f;      //最大落下速度
        bool m_nowJump;                             //ジャンプ状態判定
        std::function<bool()> m_trigger;            //トリガー
    };
}

