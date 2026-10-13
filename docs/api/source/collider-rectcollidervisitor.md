# Collider.RectColliderVisitor

当たり判定関連 / 矩形コライダービジター

所属：[collisionのAPI解説](../collision.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Collision/RectCollider/RectColliderVisitor.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Collision/RectCollider/RectColliderVisitor.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Collider.RectColliderVisitor;
import ColliderVisitor;
import Collider.RectColliderResolver;
import MyLib.Math.Vector2;

using namespace math;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{
    // 前方宣言
    class RectCollider;
    class CircleCollider;

    /// <summary>
    /// 矩形コライダービジター
    /// </summary>
    /// <remarks>
    export class RectColliderVisitor final : public ColliderVisitor
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        RectColliderVisitor(RectCollider& issue);

        // デフォルトコンストラクタは削除
        RectColliderVisitor() = delete;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~RectColliderVisitor() = default;

        /// <summary>
        /// 矩形コライダーを訪問
        /// </summary>
        /// <param name="_target">訪問する矩形コライダー</param>
        void Visit(RectCollider& target) override;

        /// <summary>
        /// 円形コライダーを訪問
        /// </summary>
        /// <param name="_target">訪問する円形コライダー</param>
        void Visit(CircleCollider& target) override;

    private:
        RectCollider& m_issue; // 訪問する矩形コライダーの参照
        RectColliderResolver m_resolver; // 矩形コライダーの解決処理を行うリゾルバー
    };
}
```
