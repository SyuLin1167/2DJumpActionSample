export module Collider.RectColliderVisitor;

import ColliderVisitor;
import Collider.RectColliderResolver;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{
    // 前方宣言
    export class RectCollider;

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
        RectColliderVisitor(RectCollider& issue) :m_issue(issue) {}

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
        void Visit(col2d::RectCollider& target) override;

    private:
        RectCollider& m_issue; // 訪問する矩形コライダーの参照
        RectColliderResolver m_resolver; // 矩形コライダーの解決処理を行うリゾルバー
    };
}
