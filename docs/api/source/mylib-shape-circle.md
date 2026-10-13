# MyLib.Shape.Circle

形状関連 / 円

所属：[mylibのAPI解説](../mylib.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/include/MyLib/Shape/Circle.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/include/MyLib/Shape/Circle.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module MyLib.Shape.Circle;
import MyLib.Math.Vector2;

using namespace math;

/// <summary>
/// 形状関連
/// </summary>
export namespace shape
{
    /// <summary>
    /// 円
    /// </summary>
    export struct Circle
    {
        Vector2f center; // 中心座標
        float radius; // 半径

        /// <summary>
        /// コンストラクタ
        /// </summary>
        Circle() :center({ 0,0 }), radius(0.0f) {};

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="center">中心座標</param>
        /// <param name="radius">半径</param>
        Circle(const Vector2f& center, const float& radius) : center(center), radius(radius) {};

        /// <summary>
        /// 点が円の内部にあるか判定
        /// </summary>
        /// <param name="point">判定する点</param>
        /// <returns>円の内部にあるかどうか</returns>
        bool IsInside(const Vector2f& point) const
        {
            Vector2f diff = point - center;
            return diff.LengthSq() <= radius * radius;
        }

        /// <summary>
        /// 円同士の重なり判定
        /// </summary>
        /// <param name="other">判定する円</param>
        /// <returns>重なっているかどうか</returns>
        bool IsInside(const Circle& other) const
        {
            Vector2f diff = other.center - center;
            float rSum = radius + other.radius;
            return diff.LengthSq() <= rSum * rSum;
        }
    };
}
```
