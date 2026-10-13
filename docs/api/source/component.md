# Component

コンポーネント関連 / コンポーネントの基底クラス

所属：[componentのAPI解説](../component.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Component/ComponentBase/ComponentBase.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Component/ComponentBase/ComponentBase.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Component;

// 前方宣言
export namespace object
{
    class GameObject;
}

/// <summary>
/// コンポーネント関連
/// </summary>
export namespace component
{
    /// <summary>
    /// コンポーネントの基底クラス
    /// </summary>
    export class ComponentBase
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
        /// 更新処理
        /// </summary>
        /// <param name="deltaTime">デルタタイム</param>
        virtual void Update(const float& deltaTime) {};

        /// <summary>
        /// 描画処理
        /// </summary>
        virtual void Draw() {};

    protected:
        class object::GameObject* m_owner;  //所有者
    };
}
```
