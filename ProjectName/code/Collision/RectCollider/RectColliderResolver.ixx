export module Collider.RectColliderResolver;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{
    // 前方宣言
    export class RectCollider;

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
        /// <param name="issue">解決対象のタイルコライダー</param>
        /// <param name="other">他の矩形コライダー</param>
        void Resolve(RectCollider& issue, const RectCollider& other);
    };
}
