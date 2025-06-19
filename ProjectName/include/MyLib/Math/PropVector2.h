#pragma once
#include "Vector2.h"

namespace math
{
    /// <summary>
    /// �񎟌��x�N�g��(����)
    /// </summary>
    /// <typeparam name="T">�^</typeparam>
    template<typename T>
    class PropVector2 final
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        PropVector2() = default;

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="owner">�A�N�Z�X���̓񎟌��x�N�g��</param>
        explicit PropVector2(Vector2<T>& _owner) :owner(_owner) {};

        /// <summary>
        /// ���Z
        /// </summary>
        /// <param name="Axis">���Z�Ώۂ̎�</param>
        /// <param name="value">���Z����l</param>
        void Add(T Vector2<T>::* _axis, T _value)
        {
            owner.*_axis += _value;
        }

        /// <summary>
        /// ���Z
        /// </summary>
        /// <param name="_other">���Z�x�N�g��</param>
        void Add(Vector2<T> _other)
        {
            owner += _other;
        }

        /// <summary>
        /// ���
        /// </summary>
        /// <param name="Axis">����Ώۂ̎�</param>
        /// <param name="value">�������l</param>
        void Assign(T Vector2<T>::* Axis, T value)
        {
            owner.*Axis = value;
        }

        /// <summary>
        /// ���
        /// </summary>
        /// <param name="_otherX">�������lX</param>
        /// <param name="_otherY">�������lY</param>
        void Assign(T _otherX, T _otherY)
        {
            owner = Vector2<T>(_otherX, _otherY);
        }

        /// <summary>
        /// ���
        /// </summary>
        /// <param name="_other">�������x�N�g���l</param>
        void Assign(Vector2<T> _other)
        {
            owner = _other;
        }

        Vector2<T>& NowPos() const
        {
            return owner;
        }

        /// <summary>
        /// ���݂�X�̒l
        /// </summary>
        /// <returns>X�̒l</returns>
        T NowX() const
        {
            return owner.x;
        }

        /// <summary>
         /// ���݂�X�̒l
         /// </summary>
         /// <typeparam name="U">�^</typeparam>
         /// <returns>X�̒l</returns>
        template<typename U>
        U NowX() const
        {
            return static_cast<U>(owner.x);
        }

        /// <summary>
        /// ���݂�Y�̒l
        /// </summary>
        /// <returns>Y�̒l</returns>
        T NowY() const
        {
            return owner.y;
        }

        /// <summary>
        /// ���݂�Y�̒l
        /// </summary>
        /// <typeparam name="U">�^</typeparam>
        /// <returns>Y�̒l</returns>
        template<typename U>
        U NowY() const
        {
            return static_cast<U>(owner.y);
        }

        static constexpr auto X = &Vector2<T>::x;  //X��
        static constexpr auto Y = &Vector2<T>::y;  //Y��

    private:
        Vector2<T>& owner;   //�Q�Ƃ���񎟌��x�N�g��
    };
}
