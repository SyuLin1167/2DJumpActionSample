export module Collider.RectCollider;

import MyLib.Shape.Rect;
import Collider;
import Collider.RectColliderVisitor;

using namespace math;

/// <summary>
/// 当たり判定関連
/// </summary>
export namespace col2d
{ 
    /// <summary>
    /// 矩形コライダー
    /// </summary>
    export class RectCollider final : public Collider
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_def">コライダー定義</param>
        RectCollider(ColliderDef* _def);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~RectCollider() override = default;

        /// <summary>
        /// カテゴリーの生成
        /// </summary>
        /// <param name="_ownerID">所有者のID</param>
        void GenerateCategory(uint32_t _ownerID = 0) override
        {
            m_filter.category = MakeKey(ShapeType::RECT, _ownerID);
        }

        /// <summary>
        /// 初期化
        /// </summary>
        /// <param name="_size">サイズ</param>
        void Initialize(const Vector2f& _size = { 0.0f,0.0f });

        /// <summary>
        /// 初期化
        /// </summary>
        /// <param name="width">幅</param>
        /// <param name="height">高さ</param>
        inline void Initialize(const float& width, const float& height)
        {
            Initialize({ width, height });
        }

        /// <summary>
        /// 矩形(シェイプ)を取得
        /// </summary>
        /// <returns>サイズ</returns>
        shape::Rect GetRect() const
        {
            return m_baseRect;
        }

        /// <summary>
        /// スイープ矩形を取得
        /// </summary>
        shape::Rect GetSweptRect() const
        {
            return m_baseRect;
        }

        /// <summary>
        /// 矩形と点の衝突判定
        /// </summary>
        /// <param name="point">衝突判定を行う点</param>
        /// <returns>衝突している場合はtrue、そうでない場合はfalse</returns>
        [[nodiscard]] bool IsColliding(const Vector2f& point);

        /// <summary>
        /// 矩形同士の衝突判定
        /// </summary>
        /// <param name="other">衝突判定を行う他の矩形コライダー</param>
        /// <returns>衝突している場合はtrue、そうでない場合はfalse</returns>
        [[nodiscard]] bool IsColliding(const RectCollider& other);

        /// <summary>
        /// コライダーを訪問
        /// </summary>
        /// <param name="visitor">訪問するビジター</param>
        void Accept(ColliderVisitor& visitor) override
        {
            visitor.Visit(*this);
        }

        /// <summary>
        /// 他のコライダーとの衝突判定
        /// </summary>
        /// <param name="_other">他のコライダー</param>
        void CollideWith(Collider& _other) override
        {
            _other.Accept(*m_visitor);
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
        void AddVelocity()
        {
            m_colDef->localPos += m_velocity;
            m_baseRect.pos = m_colDef->localPos;
        }

    private:
        /// <summary>
        /// スイープ矩形を算出
        /// </summary>
        void CalcSweptRect(Vector2f velocity);

        std::unique_ptr<RectColliderVisitor> m_visitor; // ビジター
        shape::Rect m_baseRect;                         // 基本の矩形
        shape::Rect m_sweptRect;                        // スイープ矩形
    };
}
