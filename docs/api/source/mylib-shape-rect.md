# MyLib.Shape.Rect

形状関連 / 矩形

所属：[mylibのAPI解説](../mylib.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/include/MyLib/Shape/Rect.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/include/MyLib/Shape/Rect.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module MyLib.Shape.Rect;
import MyLib.Math.Vector2;

using namespace math;

/// <summary>
/// 形状関連
/// </summary>
export namespace shape
{
    /// <summary>
    /// 矩形
    /// </summary>
    export struct Rect
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
        /// <param name="pos">座標</param>
        /// <param name="size">サイズ</param>
        Rect(const Vector2f& pos, Vector2f size) : pos(pos), size(size) {};

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

        bool IsInside(const Vector2f& point) const
        {
            return (point.x >= Left() &&
                point.x <= Right() &&
                point.y >= Top() &&
                point.y <= Bottom());
        };

        /// <summary>
        /// 矩形の衝突判定
        /// </summary>
        bool AABB(const Rect& other) const
        {
            return (Left() <= other.Right() &&
                Right() >= other.Left() &&
                Top() <= other.Bottom() &&
                Bottom() >= other.Top());
        };
    };
}
```
