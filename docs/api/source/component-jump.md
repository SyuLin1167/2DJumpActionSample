# Component.Jump

コンポーネント関連 / ジャンプ処理

所属：[componentのAPI解説](../component.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Component/Jump/Jump.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Component/Jump/Jump.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
module;
#include <functional>

export module Component.Jump;

import Component;

/// <summary>
/// コンポーネント関連
/// </summary>
export namespace component
{
    constexpr float GRAVITY = 30.0f;             //重力加速度
    constexpr float DEFAULT_JUMP_POWER = 50.0f;  //デフォルトのジャンプ力

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
        /// <param name="jumpPower">ジャンプ力</param>
        /// <param name="trigger">ジャンプのためのトリガー</param>
        Jump(object::GameObject* owner, const float& jumpPower = DEFAULT_JUMP_POWER, std::function<bool()> trigger = {});

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
        void TryJump(const float& deltaTime);

        /// <summary>
        /// ジャンプ可能にする
        /// </summary>
        void CanJump()
        {
            m_canJump = true;
            m_isGround = true;
            m_verticalSpeed = 0.0f;
        }

    private:
        const float JUMP_POWER;    //ジャンプ力
        static constexpr float MAX_FALL_VELOCITY = 300.0f;      //最大落下速度
        bool m_isGround;                             //地面にいるか
        bool m_canJump{ false };
        float m_verticalSpeed; // 垂直速度
        std::function<bool()> m_trigger;            //トリガー
    };
}
```
