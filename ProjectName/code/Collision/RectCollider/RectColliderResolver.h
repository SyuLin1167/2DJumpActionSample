#pragma once

/// <summary>
/// 当たり判定関連
/// </summary>
namespace col2d
{
    class RectCollider;

    /// <summary>
    /// 矩形コライダーの解決処理
    /// </summary>
    /// <remarks>
    /// 矩形コライダーの衝突解決を行う
    /// </remarks>
    class RectColliderResolver
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
        /// <param name="_issue">解決対象のタイルコライダー</param>
        /// <param name="_other">他の矩形コライダー</param>
        void Resolve(RectCollider& _issue, const RectCollider& _other);
    };
}
