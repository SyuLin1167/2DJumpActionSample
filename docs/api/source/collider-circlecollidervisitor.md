# Collider.CircleColliderVisitor

当たり判定関連 / 円形コライダービジター

所属：[collisionのAPI解説](../collision.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Collision/CircleColldier/CircleColliderVisitor.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Collision/CircleColldier/CircleColliderVisitor.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Collider.CircleColliderVisitor;
import ColliderVisitor;
import Collider.CircleColliderResolver;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{
    // 前方宣言
    class CircleCollider;
    class RectCollider;

    /// <summary>
    /// 円形コライダービジター
    /// </summary>
    export class CircleColliderVisitor final : public ColliderVisitor
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        CircleColliderVisitor(CircleCollider& issue);

        // デフォルトコンストラクタは削除
        CircleColliderVisitor() = delete;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~CircleColliderVisitor() = default;

        /// <summary>
        /// 矩形コライダーを訪問
        /// </summary>
        void Visit(RectCollider& target) override;

        /// <summary>
        /// 円形コライダーを訪問
        /// </summary>
        void Visit(CircleCollider& target) override;

    private:
        CircleCollider& m_issue;                 // 衝突判定を行う円形コライダー
        CircleColliderResolver m_resolver;       // 解決処理
    };
}
```
