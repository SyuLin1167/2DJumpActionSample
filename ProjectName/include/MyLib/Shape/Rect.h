#pragma once
#include"Math/Vector2.h"

using namespace math;

/// <summary>
/// 形状関連
/// </summary>
namespace shape
{
    /// <summary>
    /// 矩形
    /// </summary>
    struct Rect
    {
    public:
        Vector2<float> pos;     //座標(左上)
        Vector2<float> size;    //サイズ

        /// <summary>
        /// コンストラクタ
        /// </summary>
        Rect() :pos(), size() {};

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_pos">座標</param>
        /// <param name="_size">サイズ</param>
        Rect(Vector2<float>& _pos, Vector2<float> _size) : pos(_pos), size(_size) {};

        /// <summary>
        /// 中心座標
        /// </summary>
        /// <returns>中心座標</returns>
        Vector2<float> Center() const
        {
            return pos + size.Half();
        }

        /// <summary>
        /// 左座標
        /// </summary>
        /// <returns>x座標</returns>
        const float Left() const
        {
            return pos.x;
        }

        /// <summary>
        /// 右座標
        /// </summary>
        /// <returns>x座標+横幅</returns>
        const float Right() const
        {
            return pos.x + size.x;
        }

        /// <summary>
        /// 頂点座標
        /// </summary>
        /// <returns>y座標</returns>
        const float Top() const
        {
            return pos.y;
        }

        /// <summary>
        /// 底辺座標
        /// </summary>
        /// <returns>y座標+高さ</returns>
        const float Bottom() const
        {
            return pos.y + size.y;
        }
    };
}
