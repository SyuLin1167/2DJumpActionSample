# UI.UIBase

UI関連 / UI要素の基底クラス

所属：[uiのAPI解説](../ui.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/UI/UIBase/UIBase.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/UI/UIBase/UIBase.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module UI.UIBase;

import <vector>;
import <functional>;
import MyLib.Math.Vector2;

using namespace math;

/// <summary>
/// UI関連
/// </summary>
export namespace ui
{
    /// <summary>
    /// UI要素の基底クラス
    /// </summary>
    export class UIBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        UIBase(): m_pos{ 0.0f, 0.0f }, m_size{ 0.0f, 0.0f }, m_visible{ true } {}

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~UIBase() = default;

        /// <summary>
        /// 位置設定
        /// </summary>
        /// <param name="pos">位置</param>
        void SetPosition(const Vector2f& pos)
        {
            m_pos = pos;
        }

        /// <summary>
        /// サイズ設定
        /// </summary>
        /// <param name="size">サイズ</param>
        void SetSize(const Vector2f& size)
        {
            m_size = size;
        }

        /// <summary>
        /// 表示設定
        /// </summary>
        /// <param name="visible">表示状態</param>
        void SetVisible(bool visible)
        {
            m_visible = visible;
        }

        /// <summary>
        /// 位置取得
        /// </summary>
        /// <returns>位置</returns>
        const Vector2f& GetPosition() const
        {
            return m_pos;
        }

        /// <summary>
        /// サイズ取得
        /// </summary>
        /// <returns>サイズ</returns>
        const Vector2f& GetSize() const
        {
            return m_size;
        }

        /// <summary>
        /// 表示状態取得
        /// </summary>
        /// <returns>表示状態</returns>
        bool IsVisible() const
        {
            return m_visible;
        }

        /// <summary>
        /// 更新処理
        /// </summary>
        virtual void Update() {}

        /// <summary>
        /// 描画処理
        /// </summary>
        virtual void Draw() {}

    protected:
        Vector2f m_pos;     // 位置
        Vector2f m_size;    // サイズ
        bool m_visible;     // 表示状態
    };
}
```
