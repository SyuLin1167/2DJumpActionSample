#pragma once
#include "TileColliderResolver.h"
#include "Collider/ColliderVisitor.h"

namespace col2d
{
    // 前方宣言
    class TileCollider;

    /// <summary>
    /// タイルコライダービジター
    /// </summary>
    class TileColliderVisitor final : public ColliderVisitor
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="issue">訪問するタイルコライダー</param>
        TileColliderVisitor(TileCollider& issue) : m_issue(issue) {}

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

    private:
        TileCollider& m_issue;              // 訪問するタイルコライダーの参照
        TileColliderResolver m_resolver;    // タイルコライダーの解決処理を行うリゾルバー
    };
}
