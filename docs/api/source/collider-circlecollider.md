# Collider.CircleCollider

当たり判定関連 / 円形コライダー

所属：[collisionのAPI解説](../collision.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Collision/CircleColldier/CircleCollider.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Collision/CircleColldier/CircleCollider.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Collider.CircleCollider;

import MyLib.Shape.Circle;
import MyLib.Shape.Rect;
import MyLib.Math.Vector2;
import Collider;

using namespace math;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{
    // 前方宣言
    class RectCollider;

    /// <summary>
    /// 円形コライダー
    /// </summary>
    export class CircleCollider final : public Collider
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        CircleCollider(ColliderDef* def, float radius = 0.0f);

        // デフォルトコンストラクタは削除
        CircleCollider() = delete;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~CircleCollider() override;

        /// <summary>
        /// カテゴリーの生成
        /// </summary>
        /// <param name="_ownerID">所有者のID</param>
        void GenerateCategory(uint32_t _ownerID = 0) override
        {
            m_filter.category = MakeKey(ShapeType::CIRCLE, _ownerID);
        }

        /// <summary>
        /// 円形を取得
        /// </summary>
        /// <returns>円形</returns>
        shape::Circle GetCircle() const
        {
            return m_baseCircle;
        }

        /// <summary>
        /// 点との衝突判定
        /// </summary>
        /// <param name="point">衝突判定を行う点</param>
        /// <returns>衝突しているかどうか</returns>
        bool IsCollider(const Vector2f& point);

        /// <summary>
        /// 点との連続衝突検出判定
        /// </summary>
        /// <param name="point">衝突判定を行う点</param>
        /// <returns>衝突しているかどうか</returns>
        inline bool IsColliderSegmentPoint(const Vector2f& point);

        /// <summary>
        /// 矩形との衝突判定
        /// </summary>
        /// <param name="other">衝突判定を行う矩形</param>
        /// <returns>衝突しているかどうか</returns>
        bool IsCollider(const RectCollider& other);

        /// <summary>
        /// 矩形との連続衝突検出判定
        /// </summary>
        /// <param name="rect">衝突判定を行う矩形</param>
        /// <returns>衝突しているかどうか</returns>
        inline bool IsColliderSegmentRect(const shape::Rect& rect);
        
        /// <summary>
        /// 他の円形との衝突判定
        /// </summary>
        /// <param name="other">衝突判定を行う円形</param>
        /// <returns>衝突しているかどうか</returns>
        bool IsCollider(const CircleCollider& other);

        /// <summary>
        /// 円形との連続衝突検出判定
        /// </summary>
        /// <param name="other">衝突判定を行う円形</param>
        /// <returns>衝突しているかどうか</returns>
        inline bool IsColliderSegmentCircle(const CircleCollider& other);

        /// <summary>
        /// コライダーを訪問
        /// </summary>
        /// <param name="visitor">訪問するビジター</param>
        void Accept(ColliderVisitor& visitor) override;

        /// <summary>
        /// 移動量の追加
        /// </summary>
        void AddVelocity(const Vector2f& velocity) override
        {
            m_colDef->localPos += velocity;
            m_baseCircle.center = m_colDef->localPos;
        }

        /// <summary>
        /// 移動量の追加
        /// </summary>
        void AddVelocity() override
        {
            m_colDef->localPos += m_velocity;
            m_baseCircle.center = m_colDef->localPos;
        }

    private:
        shape::Circle m_baseCircle;     // 基本円形
    };
}
```
