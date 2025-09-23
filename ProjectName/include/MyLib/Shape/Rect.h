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
        Vector2f pos;     //座標(左上)
        Vector2f size;    //サイズ

        /// <summary>
        /// コンストラクタ
        /// </summary>
        Rect() :pos(), size() {};

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_pos">座標</param>
        /// <param name="_size">サイズ</param>
        Rect(Vector2f& _pos, Vector2f _size) : pos(_pos), size(_size) {};

        /// <summary>
        /// 中心座標
        /// </summary>
        /// <returns>中心座標</returns>
        Vector2f Center() const
        {
            return pos + size.Half();
        }

        /// <summary>
        /// 左座標
        /// </summary>
        /// <returns>x座標</returns>
        float Left() const
        {
            return pos.x;
        }

        /// <summary>
        /// 右座標
        /// </summary>
        /// <returns>x座標+横幅</returns>
        float Right() const
        {
            return pos.x + size.x;
        }

        /// <summary>
        /// 頂点座標
        /// </summary>
        /// <returns>y座標</returns>
        float Top() const
        {
            return pos.y;
        }

        /// <summary>
        /// 底辺座標
        /// </summary>
        /// <returns>y座標+高さ</returns>
        float Bottom() const
        {
            return pos.y + size.y;
        }

        /// <summary>
        /// 矩形の衝突判定
        /// </summary>
        bool AABB(const Rect& _other) const
        {
            return (Left() < _other.Right() &&
                Right() > _other.Left() &&
                Top() < _other.Bottom() &&
                Bottom() > _other.Top());
        };
    };
}
