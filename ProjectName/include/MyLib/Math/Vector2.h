#pragma once
#include <cmath>
#include <memory>

/// <summary>
/// 数学関連
/// </summary>
namespace math
{
    /// <summary>
    /// 二次元ベクトル
    /// </summary>
    /// <typeparam name="T">型</typeparam>
    template<typename T>
    struct Vector2
    {
        T x;    //x
        T y;    //y

        /// <summary>
        /// コンストラクタ
        /// </summary>
        Vector2() = default;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_x">入力値X</param>
        /// <param name="_y">入力値Y</param>
        constexpr Vector2(T _x, T _y) : x(_x), y(_y) {}

        /// <summary>
        /// 自身の長さ
        /// </summary>
        /// <returns>自身の長さ</returns>
        constexpr T Length() const
        {
            return std::sqrt<T>(x * x + y * y);
        }

        /// <summary>
        /// 正規化
        /// </summary>
        /// <returns>正規化後の値</returns>
        constexpr Vector2<T> Norm() const
        {
            if (T len = Length(); len > 0)
            {
                return { x / len, y / len };
            }
            return Vector2<T>(0, 0);
        }

        /// <summary>
        /// 自身との距離
        /// </summary>
        /// <param name="_other">対象のベクトル</param>
        /// <returns>自身と対象との距離</returns>
        constexpr T Distance(const Vector2& _other) {

            return std::sqrt<T>((x - _other.x) * (x - _other.x) + (y - _other.y) * (y - _other.y));
        }

        /// <summary>
        /// 二等分
        /// </summary>
        /// <returns>二等分した値</returns>
        constexpr Vector2<T> Half() const
        {
            return Vector2<T>(x / 2, y / 2);
        }

        /// <summary>
        /// 加算
        /// </summary>
        /// <param name="_other">加算ベクトル</param>
        /// <returns>加算後のベクトル</returns>
        template<typename U>
        constexpr Vector2 operator +(const Vector2<U>& _other) const
        {
            return Vector2(x + static_cast<T>(_other.x), y + static_cast<T>(_other.y));
        }

        /// 加算
        /// </summary>
        /// <param name="_other">加算ベクトル</param>
        /// <returns>加算後のベクトル</returns>
        template<typename U>
        constexpr Vector2 operator +=(const Vector2<U>& _other) const
        {
            x += static_cast<T>(_other.x);
            y += static_cast<T>(_other.y);
            return *this;
        }

        /// <summary>
        /// 減算
        /// </summary>
        /// <param name="_other">減算ベクトル</param>
        /// <returns>減算後のベクトル</returns>
        template<typename U>
        constexpr Vector2 operator -(const Vector2<U>& _other) const
        {
            return Vector2(x - static_cast<T>(_other.x), y - static_cast<T>(_other.y));
        }

        /// <summary>
        /// 減算
        /// </summary>
        /// <param name="_other">減算ベクトル</param>
        /// <returns>減算後のベクトル</returns>
        template<typename U>
        constexpr Vector2 operator -=(const Vector2<U>& _other) const
        {
            x -= static_cast<T>(_other.x);
            y -= static_cast<T>(_other.y);
            return *this;
        }

        /// <summary>
        /// 乗算
        /// </summary>
        /// <param name="_other">乗算値</param>
        /// <returns>乗算後のベクトル</returns>
        template<typename U>
        constexpr Vector2 operator *(const Vector2<U>& _other) const
        {
            return Vector2(x * static_cast<T>(_other.x), y * static_cast<T>(_other.y));
        }

        /// <summary>
        /// 乗算
        /// </summary>
        /// <param name="_other">乗算値</param>
        /// <returns>乗算後のベクトル</returns>
        template<typename U>
        constexpr Vector2 operator *=(const Vector2<U>& _other) const
        {
            x *= static_cast<T>(_other.x);
            y *= static_cast<T>(_other.y);
            return *this;
        }

        /// <summary>
        /// 除算
        /// </summary>
        /// <param name="_other">除算値</param>
        /// <returns>除算後のベクトル</returns>
        template<typename U>
        constexpr Vector2 operator /(const Vector2<U>& _other) const
        {
            return Vector2(x / static_cast<T>(_other.x), y / static_cast<T>(_other.y));
        }

        /// <summary>
        /// 除算
        /// </summary>
        /// <param name="_other">除算値</param>
        /// <returns>除算後のベクトル</returns>
        template<typename U>
        constexpr Vector2 operator /=(const Vector2<U>& _other) const
        {
            x /= static_cast<T>(_other.x);
            y /= static_cast<T>(_other.y);
            return *this;
        }

        /// <summary>
        /// 代入
        /// </summary>
        /// <param name="_other">代入するベクトル</param>
        /// <returns>代入後のベクトル</returns>
        template<typename U>
        constexpr Vector2 operator =(const Vector2<U>& _other)
        {
            x = static_cast<T>(_other.x);
            y = static_cast<T>(_other.y);
            return *this;
        }
    };
}
