# Collider.TileColliderResolver

当たり判定関連 / タイルコライダーの解決処理

所属：[collisionのAPI解説](../collision.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Collision/TileCollider/TileColliderResolver.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Collision/TileCollider/TileColliderResolver.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Collider.TileColliderResolver;
import <cstdint>;
import <optional>;
import Collider.RectCollider;
import Collider.TileCollider;
import MyLib.Shape.Rect;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{
    /// <summary>
    /// タイルコライダーの解決処理
    /// </summary>
    /// <remarks>
    /// タイルコライダーの衝突解決を行う
    /// </remarks>
    export class TileColliderResolver
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        TileColliderResolver() = default;
        /// <summary>
        /// デストラクタ
        /// </summary>
        ~TileColliderResolver() = default;

        /// <summary>
        /// 解決処理
        /// </summary>
        /// <param name="issue">解決対象のタイルコライダー</param>
        /// <param name="tileInfo">タイル情報</param>
        /// <returns>衝突情報</returns>
        std::optional<ContactInfo> Resolve(RectCollider& issue, const TileInfo& tileInfo);

        // 押し戻し量の計算
        math::Vector2f CalcPushBack(const RectCollider& issue,const uint8_t adjacentFlag, const shape::Rect& tileRect);

        /// <summary>
        /// 通常ブロックの解決処理
        /// </summary>
        /// <param name="issue">解決対象のタイルコライダー</param>
        /// <param name="tileInfo">タイル情報</param
        /// <returns>衝突情報</returns>
        std::optional<ContactInfo> ResolveSolid(RectCollider& issue, const TileInfo& tileInfo);

        /// <summary>
        /// 上からのみ当たるブロックの解決処理
        /// </summary>
        /// <param name="issue">解決対象のタイルコライダー</param>
        /// <param name="tileInfo">タイル情報</param>
        /// <returns>衝突情報</returns>
        std::optional<ContactInfo> ResolveOneWayTop(RectCollider& issue, const TileInfo& tileInfo);
    };
}
```
