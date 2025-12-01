export module Collider.TileColliderVisitor;
export import ColliderVisitor;
import Collider.TileColliderResolver;

export namespace col2d
{
    // 前方宣言
    class TileCollider;
    class CircleCollider;

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

        // 衝突タイル毎に処理
        void ProcessCollisionTiles(RectCollider& collider);

    private:
        TileCollider& m_issue;              // 訪問するタイルコライダーの参照
        TileColliderResolver m_resolver;    // タイルコライダーの解決処理を行うリゾルバー
    };
}
