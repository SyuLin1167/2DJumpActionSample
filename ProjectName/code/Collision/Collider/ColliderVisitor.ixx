export module ColliderVisitor;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{
    // 前方宣言
    export class RectCollider;
    export class CircleCollider;

    /// <summary>
    /// コライダービジター
    /// </summary>
    export class ColliderVisitor
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        ColliderVisitor() = default;
        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~ColliderVisitor() = default;

        /// <summary>
        /// 矩形コライダーへ訪問
        /// </summary>
        virtual void Visit(RectCollider& target) {};

        /// <summary>
        /// 円形コライダーへ訪問
        /// </summary>
        virtual void Visit(CircleCollider& target) {};
    };
}
