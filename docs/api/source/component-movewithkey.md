# Component.MoveWithKey

コンストラクタ / デストラクタ

所属：[componentのAPI解説](../component.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Component/Move/MoveWithKey/MoveWithKey.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Component/Move/MoveWithKey/MoveWithKey.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Component.MoveWithKey;

import Component;
export import MyLib.Math.Vector2;

export using namespace math;

export namespace component
{
    export class MoveWithKey final :public ComponentBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="owner">所有者</param>
        MoveWithKey(object::GameObject* owner);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~MoveWithKey() = default;

        /// <summary>
        /// 水平移動の設定
        /// </summary>
        /// <param name="leftKey">左へ移動するためのキー</param>
        /// <param name="rightKey">右へ移動するためのキー</param>
        /// <param name="moveSpeed">移動速度</param>
        void SetHorizontal(const int leftKey, const int rightKey, float moveSpeed);

        /// <summary>
        /// 垂直移動の設定
        /// </summary>
        /// <param name="upKey">上へ移動するためのキー</param>
        /// <param name="downKey">下へ移動するためのキー</param>
        /// <param name="moveSpeed">移動速度</param>
        void SetVertical(const int upKey, const int downKey, float moveSpeed);

        /// <summary>
        /// 更新
        /// </summary>
        /// <param name="deltaTime">デルタタイム</param>
        void Update(const float& deltaTime) override;

        /// <summary>
        ///　X軸移動が可能かどうか
        /// </summary>
        /// <returns>移動可否情報</returns>
        const bool CanMoveHorizontal()
        {
            return m_canMoveX;
        }

        /// <summary>
        /// Y軸移動が可能かどうか
        /// </summary>
        /// <returns>移動可否情報</returns>
        const bool CanMoveVertical()
        {
            return m_canMoveY;
        }

    private:
        int m_leftKey;
        int m_rightKey;
        int m_upKey;
        int m_downKey;
        Vector2f m_moveSpeed;
        bool m_canMoveX;
        bool m_canMoveY;
    };
}
```
