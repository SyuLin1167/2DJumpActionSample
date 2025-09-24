#pragma once

/// <summary>
/// 当たり判定関連
/// </summary>
namespace col2d
{
    class RectCollider;

    /// <summary>
    /// コライダービジター
    /// </summary>
    /// <remarks>
    /// コライダーに対するビジター
    /// </remarks>
    class ColliderVisitor
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
        /// 矩形コライダーを訪問
        /// </summary>
        /// <param name="_target">訪問する矩形コライダー</param>
        virtual void Visit(RectCollider& _target) = 0;
    };
}
