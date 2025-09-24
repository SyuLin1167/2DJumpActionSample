#pragma once
#include "RectCollider/RectCollider.h"

/// <summary>
/// 当たり判定関連
/// </summary>
namespace col2d
{
    /// <summary>
    /// タイルコライダーの解決処理
    /// </summary>
    /// <remarks>
    /// タイルコライダーの衝突解決を行う
    /// </remarks>
    class TileColliderResolver
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        TileColliderResolver() = default;
        /// <summary>
        /// デストラクタ
        /// </summary>
        ~TileColliderResolver() = default;

        /// <summary>
        /// 解決処理
        /// </summary>
        /// <param name="_issue">解決対象のタイルコライダー</param>
        /// <param name="_other">他の矩形コライダー</param>
        /// <param name="_adjacentFlag">隣接するタイルのフラグ</param>
        void Resolve(RectCollider& _issue, const RectCollider& _other,const uint8_t& _adjacentFlag);
    };
}

