#pragma once
#include "TileColliderResolver.h"
#include "ColliderVisitor/ColliderVisitor.h"

namespace col2d
{
    class TileCollider;

    class TileColliderVisitor final : public ColliderVisitor
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        TileColliderVisitor(TileCollider& _issue) : issue(_issue) {}

        // デフォルトコンストラクタは削除
        TileColliderVisitor() = delete;
        /// <summary>
        /// デストラクタ
        /// </summary>
        ~TileColliderVisitor() = default;

        /// <summary>
        /// タイルコライダーを訪問
        /// </summary>
        /// <param name="_collider">訪問するタイルコライダー</param>
        void Visit(RectCollider& _collider) override;

    private:
        TileCollider& issue; // 訪問するタイルコライダーの参照
        TileColliderResolver resolver; // タイルコライダーの解決処理を行うリゾルバー
    };
}
