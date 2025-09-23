#pragma once
#include "math/Vector2.h"

using namespace math;

/// <summary>
/// 当たり判定関連
/// </summary>
namespace col2d
{
    /// <summary>
    /// コライダー定義
    /// </summary>
    /// <remarks>
    /// コライダーの定義情報を保持する
    /// </remarks>
    struct ColliderDef final
    {
        /// <summary>
        /// コンストラクタ
        /// </summary>
        ColliderDef() = default;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~ColliderDef() = default;

        Vector2f worldPos;   // ワールド座標
        Vector2f localPos;   // ローカル座標
        bool shouldCCD;     // 連続衝突検出を行うか
        bool isTrigger;     // トリガーかどうか
        bool isActive;      // 有効かどうか
    };
}


