#pragma once
#include "Vector2.h"

namespace math
{
    /// <summary>
    /// 二次元ベクトル(属性)
    /// </summary>
    /// <typeparam name="T">型</typeparam>
    template<typename T>
    class PropVector2 final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        PropVector2() = default;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="owner">アクセス元の二次元ベクトル</param>
        explicit PropVector2(Vector2<T>& _owner) :owner(_owner) {};

        /// <summary>
        /// 加算
        /// </summary>
        /// <param name="Axis">加算対象の軸</param>
        /// <param name="value">加算する値</param>
        void Add(T Vector2<T>::* _axis, T _value)
        {
            owner.*_axis += _value;
        }

        /// <summary>
        /// 加算
        /// </summary>
        /// <param name="_other">加算ベクトル</param>
        void Add(Vector2<T> _other)
        {
            owner += _other;
        }

        /// <summary>
        /// 代入
        /// </summary>
        /// <param name="Axis">代入対象の軸</param>
        /// <param name="value">代入する値</param>
        void Assign(T Vector2<T>::* Axis, T value)
        {
            owner.*Axis = value;
        }

        /// <summary>
        /// 代入
        /// </summary>
        /// <param name="_otherX">代入する値X</param>
        /// <param name="_otherY">代入する値Y</param>
        void Assign(T _otherX, T _otherY)
        {
            owner = Vector2<T>(_otherX, _otherY);
        }

        /// <summary>
        /// 代入
        /// </summary>
        /// <param name="_other">代入するベクトル値</param>
        void Assign(Vector2<T> _other)
        {
            owner = _other;
        }

        Vector2<T>& NowPos() const
        {
            return owner;
        }

        /// <summary>
        /// 現在のXの値
        /// </summary>
        /// <returns>Xの値</returns>
        T NowX() const
        {
            return owner.x;
        }

        /// <summary>
         /// 現在のXの値
         /// </summary>
         /// <typeparam name="U">型</typeparam>
         /// <returns>Xの値</returns>
        template<typename U>
        U NowX() const
        {
            return static_cast<U>(owner.x);
        }

        /// <summary>
        /// 現在のYの値
        /// </summary>
        /// <returns>Yの値</returns>
        T NowY() const
        {
            return owner.y;
        }

        /// <summary>
        /// 現在のYの値
        /// </summary>
        /// <typeparam name="U">型</typeparam>
        /// <returns>Yの値</returns>
        template<typename U>
        U NowY() const
        {
            return static_cast<U>(owner.y);
        }

        static constexpr auto X = &Vector2<T>::x;  //X軸
        static constexpr auto Y = &Vector2<T>::y;  //Y軸

    private:
        Vector2<T>& owner;   //参照する二次元ベクトル
    };
}
