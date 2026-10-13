# Collider.RectCollider

当たり判定関連 / 矩形コライダー

所属：[collisionのAPI解説](../collision.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Collision/RectCollider/RectCollider.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Collision/RectCollider/RectCollider.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Collider.RectCollider;
import MyLib.Shape.Rect;
import Collider;

using namespace math;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{ 
    // 前方宣言
    class RectColliderVisitor;
    class CircleCollider;

    /// <summary>
    /// 矩形コライダー
    /// </summary>
    export class RectCollider final : public Collider
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="def">コライダー定義</param>
        RectCollider(ColliderDef* def, const Vector2f& size = { 0,0 });

        // デフォルトコンストラクタは削除
        RectCollider() = delete;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~RectCollider() override;

        /// <summary>
        /// カテゴリーの生成
        /// </summary>
        /// <param name="_ownerID">所有者のID</param>
        void GenerateCategory(uint32_t _ownerID = 0) override
        {
            m_filter.category = MakeKey(ShapeType::RECT, _ownerID);
        }

        /// <summary>
        /// 矩形を取得
        /// </summary>
        /// <returns>矩形</returns>
        shape::Rect GetRect() const
        {
            return m_baseRect;
        }

        /// <summary>
        /// 矩形と点の衝突判定
        /// </summary>
        /// <param name="point">衝突判定を行う点</param>
        /// <returns>衝突しているかどうか</returns>
        bool IsColliding(const Vector2f& point);

        /// <summary>
        /// 矩形と点の連続衝突判定
        /// </summary>
        /// <param name="point">衝突判定を行う点</param>
        /// <returns>衝突しているかどうか</returns>
        bool IsCollidingSegmentPoint(const Vector2f& point);

        /// <summary>
        /// 矩形と円の衝突判定
        /// </summary>
        /// <param name="circle">衝突判定を行う円形コライダー</param>
        /// <returns>衝突しているかどうか</returns>
        bool IsColliding(const CircleCollider& circle);

        /// <summary>
        /// 矩形同士の衝突判定
        /// </summary>
        /// <param name="other">衝突判定を行う他の矩形コライダー</param>
        /// <returns>衝突しているかどうか</returns>
        bool IsColliding(const RectCollider& other);

        /// <summary>
        /// 矩形同士の連続衝突判定
        /// </summary>
        /// <param name="other">衝突判定を行う矩形コライダー</param>
        /// <returns>衝突しているかどうか</returns>
        bool IsCollidingSegmentRect(const RectCollider& other);

        /// <summary>
        /// 矩形同士の連続衝突判定
        /// </summary>
        /// <param name="other">衝突判定を行う円形コライダー</param>
        /// <returns>衝突しているかどうか</returns>
        bool IsCollidingSegmentCircle(const CircleCollider& other);

        /// <summary>
        /// コライダーを訪問
        /// </summary>
        /// <param name="visitor">訪問するビジター</param>
        void Accept(ColliderVisitor& visitor) override
        {
            visitor.Visit(*this);
        }

        /// <summary>
        /// 移動量の追加
        /// </summary>
        void AddVelocity(const Vector2f& _velocity) override
        {
            m_colDef->localPos += _velocity;
            m_baseRect.pos = m_colDef->localPos;
        }

        /// <summary>
        /// 移動量の追加
        /// </summary>
        void AddVelocity() override
        {
            m_colDef->localPos += m_velocity;
            m_baseRect.pos = m_colDef->localPos;
        }

    private:
        /// <summary>
        /// スイープ矩形を算出
        /// </summary>
        void CalcSweptRect(Vector2f velocity);

        shape::Rect m_baseRect;                         // 基本の矩形
        shape::Rect m_sweptRect;                        // スイープ矩形
    };
}
```
