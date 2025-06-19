#pragma once
#include "RectCollision/RectCollision.h"

/// <summary>
/// 当たり判定関連
/// </summary>
namespace collision
{
    constexpr int8_t LEFT = 0x0001;     //左軸
    constexpr int8_t RIGHT = 0x0002;    //右軸
    constexpr int8_t TOP = 0x0004;      //上軸
    constexpr int8_t BOTTOM = 0x0008;   //下軸

    /// <summary>
    /// 通常のボックス(Map用)
    /// </summary>
    class NomalBox
    {
    public:
        /// <summary>
        /// 
        /// </summary>
        /// <param name="_main"></param>
        /// <param name="_box"></param>
        /// <param name="_boxFlag"></param>
        void ColliderWith(RectCollision& _main, RectCollision& _box, int8_t _boxFlag);
    };
}
