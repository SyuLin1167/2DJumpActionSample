# Collider.RectColliderResolver

当たり判定関連 / 矩形コライダーの解決処理

所属：[collisionのAPI解説](../collision.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Collision/RectCollider/RectColliderResolver.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Collision/RectCollider/RectColliderResolver.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Collider.RectColliderResolver;
import <optional>;
import ColliderDef;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{
    // 前方宣言
    class RectCollider;
    class CircleCollider;

    /// <summary>
    /// 矩形コライダーの解決処理
    /// </summary>
    /// <remarks>
    /// 矩形コライダーの衝突解決を行う
    /// </remarks>
    export class RectColliderResolver final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        RectColliderResolver() = default;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~RectColliderResolver() = default;

        /// <summary>
        /// 解決処理
        /// </summary>
        /// <param name="issue">解決対象の矩形コライダー</param>
        /// <param name="other">他の矩形コライダー</param>
        std::optional<ContactInfo> Resolve(RectCollider& issue, const RectCollider& other);

        /// <summary>
        /// 解決処理
        /// </summary>
        /// <param name="issue">解決対象の矩形コライダー</param>
        /// <param name="other">他の円形コライダー</param>
        std::optional<ContactInfo> Resolve(RectCollider& issue, const CircleCollider& other);
    };
}
```
