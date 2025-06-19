#pragma once
#include "RectCollision/RectCollision.h"

/// <summary>
/// �����蔻��֘A
/// </summary>
namespace collision
{
    constexpr int8_t LEFT = 0x0001;     //����
    constexpr int8_t RIGHT = 0x0002;    //�E��
    constexpr int8_t TOP = 0x0004;      //�㎲
    constexpr int8_t BOTTOM = 0x0008;   //����

    /// <summary>
    /// �ʏ�̃{�b�N�X(Map�p)
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
