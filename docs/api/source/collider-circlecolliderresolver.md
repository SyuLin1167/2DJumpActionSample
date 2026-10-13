# Collider.CircleColliderResolver

当たり判定関連 / 円形コライダー解決

所属：[collisionのAPI解説](../collision.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Collision/CircleColldier/CircleColliderResolver.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Collision/CircleColldier/CircleColliderResolver.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Collider.CircleColliderResolver;
import <optional>;
import MyLib.Math.Vector2;
import ColliderDef;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{
    class RectCollider;
    class CircleCollider;

    /// <summary>
    /// 円形コライダー解決
    /// </summary>
    export class CircleColliderResolver
    {
    public:
        CircleColliderResolver() = default;
        ~CircleColliderResolver() = default;

        /// <summary>
        /// 解決処理
        /// </summary>
        /// <param name="issue">解決対象の円形コライダー</param>
        /// <param name="other">他の矩形コライダー</param>
        std::optional<ContactInfo> Resolve(CircleCollider& issue, const RectCollider& other);

        /// <summary>
        /// 解決処理
        /// </summary>
        /// <param name="issue">解決対象の円形コライダー</param>
        /// <param name="other">他の円形コライダー</param>
        std::optional<ContactInfo> Resolve(CircleCollider& issue, const CircleCollider& other);
    };
}
```
