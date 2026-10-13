# ColliderDef

当たり判定関連 / コライダーの種類

所属：[collisionのAPI解説](../collision.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Collision/Collider/ColliderDef.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Collision/Collider/ColliderDef.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module ColliderDef;

import MyLib.Math.Vector2;

using namespace math;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{
    /// <summary>
    /// コライダーの種類
    /// </summary>
    export enum class Type
    {
        DYNAMIC,    // 動的
        STATIC      // 静的
    };

    /// <summary>
    /// コライダー定義
    /// </summary>
    /// <remarks>
    /// コライダーの定義情報を保持する
    /// </remarks>
    export struct ColliderDef final
    {
        /// <summary>
        /// コンストラクタ
        /// </summary>
        ColliderDef() = default;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~ColliderDef() = default;

        Type type{ Type::DYNAMIC }; // コライダーの種類
        Vector2f worldPos{ 0,0 };   // ワールド座標
        Vector2f localPos{ 0,0 };   // ローカル座標
        bool shouldCCD;             // 連続衝突検出を行うか
        bool isTrigger;             // トリガーかどうか
        bool isActive;              // 有効かどうか
    };

    /// <summary>
    /// 衝突情報
    /// </summary>
    export struct ContactInfo
    {
        Vector2f normal{}; // 法線
        Vector2f point{}; // 衝突点
    };
}
```
