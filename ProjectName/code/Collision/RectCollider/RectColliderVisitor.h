#pragma once
#include "ColliderVisitor/ColliderVisitor.h"
#include "RectColliderResolver.h"

/// <summary>
/// 当たり判定関連
/// </summary>
namespace col2d
{
    class RectCollider;

    /// <summary>
    /// 矩形コライダービジター
    /// </summary>
    /// <remarks>
    /// 矩形コライダーに対するビジター
    /// </remarks>
    class RectColliderVisitor final : public ColliderVisitor
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        RectColliderVisitor(RectCollider& _issue) :issue(_issue) {}

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
        void Visit(col2d::RectCollider& _target) override;

    private:
        RectCollider& issue; // 訪問する矩形コライダーの参照
        RectColliderResolver resolver; // 矩形コライダーの解決処理を行うリゾルバー
    };
}
