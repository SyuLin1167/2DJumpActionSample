#pragma once
#include "RectCollision/RectCollision.h"

/// <summary>
/// ½è»èÖA
/// </summary>
namespace collision
{
    constexpr int8_t LEFT = 0x0001;     //¶²
    constexpr int8_t RIGHT = 0x0002;    //E²
    constexpr int8_t TOP = 0x0004;      //ã²
    constexpr int8_t BOTTOM = 0x0008;   //º²

    /// <summary>
    /// ÊíÌ{bNX(Mapp)
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
