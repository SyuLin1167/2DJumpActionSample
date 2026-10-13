# Collider.TileColliderVisitor

タイルコライダービジター / コンストラクタ

所属：[collisionのAPI解説](../collision.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Collision/TileCollider/TileColliderVisitor.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Collision/TileCollider/TileColliderVisitor.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Collider.TileColliderVisitor;
export import ColliderVisitor;
import Collider.TileColliderResolver;
import Collider.RectCollider;
import Collider.TileCollider;

export namespace col2d
{
    /// <summary>
    /// タイルコライダービジター
    /// </summary>
    export class TileColliderVisitor final : public ColliderVisitor
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="issue">訪問するタイルコライダー</param>
        TileColliderVisitor(TileCollider& issue);

        // デフォルトコンストラクタは削除
        TileColliderVisitor() = delete;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~TileColliderVisitor() = default;

        /// <summary>
        /// タイルコライダーを訪問
        /// </summary>
        /// <param name="collider">訪問するタイルコライダー</param>
        void Visit(RectCollider& collider) override;

        /// <summary>
        /// 円形コライダーを訪問
        /// </summary>
        /// <param name="target">訪問する円形コライダー</param>
        void Visit(CircleCollider& target) override
        {
            // タイルコライダーは円形コライダーに対応していないため、処理なし
        }

        /// <summary>
        /// 衝突タイル毎の処理
        /// </summary>
        /// <param name="collider">矩形コライダー</param>
        /// <param name="axis">判定軸</param>
        void ProcessCollisionTiles(RectCollider& collider);

    private:
        TileCollider& m_issue;              // 訪問するタイルコライダーの参照
        TileColliderResolver m_resolver;    // タイルコライダーの解決処理を行うリゾルバー
    };
}
```
