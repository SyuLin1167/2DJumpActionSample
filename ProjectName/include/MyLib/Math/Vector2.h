#pragma once
#include <cmath>
#include <memory>

/// <summary>
/// ���w�֘A
/// </summary>
namespace math
{
    /// <summary>
    /// �񎟌��x�N�g��
    /// </summary>
    /// <typeparam name="T">�^</typeparam>
    template<typename T>
    struct Vector2
    {
        T x;    //x
        T y;    //y

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Vector2() = default;

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="_x">���͒lX</param>
        /// <param name="_y">���͒lY</param>
        constexpr Vector2(T _x, T _y) : x(_x), y(_y) {}

        /// <summary>
        /// ���g�̒���
        /// </summary>
        /// <returns>���g�̒���</returns>
        constexpr T Length() const
        {
            return std::sqrt<T>(x * x + y * y);
        }

        /// <summary>
        /// ���K��
        /// </summary>
        /// <returns>���K����̒l</returns>
        constexpr Vector2<T> Norm() const
        {
            if (T len = Length(); len > 0)
            {
                return { x / len, y / len };
            }
            return Vector2<T>(0, 0);
        }

        /// <summary>
        /// ���g�Ƃ̋���
        /// </summary>
        /// <param name="_other">�Ώۂ̃x�N�g��</param>
        /// <returns>���g�ƑΏۂƂ̋���</returns>
        constexpr T Distance(const Vector2& _other) {

            return std::sqrt<T>((x - _other.x) * (x - _other.x) + (y - _other.y) * (y - _other.y));
        }

        /// <summary>
        /// �񓙕�
        /// </summary>
        /// <returns>�񓙕������l</returns>
        constexpr Vector2<T> Half() const
        {
            return Vector2<T>(x / 2, y / 2);
        }

        /// <summary>
        /// ���Z
        /// </summary>
        /// <param name="_other">���Z�x�N�g��</param>
        /// <returns>���Z��̃x�N�g��</returns>
        template<typename U>
        constexpr Vector2 operator +(const Vector2<U>& _other) const
        {
            return Vector2(x + static_cast<T>(_other.x), y + static_cast<T>(_other.y));
        }

        /// ���Z
        /// </summary>
        /// <param name="_other">���Z�x�N�g��</param>
        /// <returns>���Z��̃x�N�g��</returns>
        template<typename U>
        constexpr Vector2 operator +=(const Vector2<U>& _other) const
        {
            x += static_cast<T>(_other.x);
            y += static_cast<T>(_other.y);
            return *this;
        }

        /// <summary>
        /// ���Z
        /// </summary>
        /// <param name="_other">���Z�x�N�g��</param>
        /// <returns>���Z��̃x�N�g��</returns>
        template<typename U>
        constexpr Vector2 operator -(const Vector2<U>& _other) const
        {
            return Vector2(x - static_cast<T>(_other.x), y - static_cast<T>(_other.y));
        }

        /// <summary>
        /// ���Z
        /// </summary>
        /// <param name="_other">���Z�x�N�g��</param>
        /// <returns>���Z��̃x�N�g��</returns>
        template<typename U>
        constexpr Vector2 operator -=(const Vector2<U>& _other) const
        {
            x -= static_cast<T>(_other.x);
            y -= static_cast<T>(_other.y);
            return *this;
        }

        /// <summary>
        /// ��Z
        /// </summary>
        /// <param name="_other">��Z�l</param>
        /// <returns>��Z��̃x�N�g��</returns>
        template<typename U>
        constexpr Vector2 operator *(const Vector2<U>& _other) const
        {
            return Vector2(x * static_cast<T>(_other.x), y * static_cast<T>(_other.y));
        }

        /// <summary>
        /// ��Z
        /// </summary>
        /// <param name="_other">��Z�l</param>
        /// <returns>��Z��̃x�N�g��</returns>
        template<typename U>
        constexpr Vector2 operator *=(const Vector2<U>& _other) const
        {
            x *= static_cast<T>(_other.x);
            y *= static_cast<T>(_other.y);
            return *this;
        }

        /// <summary>
        /// ���Z
        /// </summary>
        /// <param name="_other">���Z�l</param>
        /// <returns>���Z��̃x�N�g��</returns>
        template<typename U>
        constexpr Vector2 operator /(const Vector2<U>& _other) const
        {
            return Vector2(x / static_cast<T>(_other.x), y / static_cast<T>(_other.y));
        }

        /// <summary>
        /// ���Z
        /// </summary>
        /// <param name="_other">���Z�l</param>
        /// <returns>���Z��̃x�N�g��</returns>
        template<typename U>
        constexpr Vector2 operator /=(const Vector2<U>& _other) const
        {
            x /= static_cast<T>(_other.x);
            y /= static_cast<T>(_other.y);
            return *this;
        }

        /// <summary>
        /// ���
        /// </summary>
        /// <param name="_other">�������x�N�g��</param>
        /// <returns>�����̃x�N�g��</returns>
        template<typename U>
        constexpr Vector2 operator =(const Vector2<U>& _other)
        {
            x = static_cast<T>(_other.x);
            y = static_cast<T>(_other.y);
            return *this;
        }
    };
}
