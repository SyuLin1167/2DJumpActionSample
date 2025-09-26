#pragma once

/// <summary>
/// 当たり判定関連
/// </summary>
namespace col2d
{
    // 前方宣言
    class RectCollider;

    /// <summary>
    /// コライダービジター
    /// </summary>
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
        virtual void Visit(RectCollider& target) = 0;
    };
}
