#pragma once
#include "Collider/Collider.h"
#include "ColliderDef/ColliderDef.h"
#include "RectColliderVisitor.h"
#include "math/Vector2.h"
#include "Shape/Rect.h"

using namespace math;

/// <summary>
/// 当たり判定関連
/// </summary>
namespace col2d
{
    class ColliderVisitor;

    /// <summary>
    /// 矩形コライダー
    /// </summary>
    /// <remarks>
    /// 矩形の形状を持つコライダー
    /// </remarks>
    class RectCollider final: public Collider
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
            filter.category = MakeKey(ShapeType::RECT, _ownerID);
        }

        /// <summary>
        /// 初期化
        /// </summary>
        /// <param name="_size">サイズ</param>
        inline void Initialize(const Vector2f& _size = { 0.0f,0.0f });

        /// <summary>
        /// 初期化
        /// </summary>
        /// <param name="_width">幅</param>
        /// <param name="_height">高さ</param>
        inline void Initialize(const float& _width, const float& _height)
        {
            Initialize({ _width,_height });
        }

        /// <summary>
        /// 矩形(シェイプ)を取得
        /// </summary>
        /// <returns>サイズ</returns>
        shape::Rect GetRect() const
        {
            return baseRect;
        }

        /// <summary>
        /// スイープ矩形を取得
        /// </summary>
        const shape::Rect GetSweptRect()
        {
            CalcSweptRect();
            return sweptRect;
        }

        /// <summary>
        /// 矩形と点の衝突判定
        /// </summary>
        /// <param name="_point">衝突判定を行う点</param>
        /// <returns>衝突している場合はtrue、そうでない場合はfalse</returns>
        bool IsColliding(const Vector2f& _point);

        /// <summary>
        /// 矩形同士の衝突判定
        /// </summary>
        /// <param name="_other">衝突判定を行う他の矩形コライダー</param>
        /// <returns>衝突している場合はtrue、そうでない場合はfalse</returns>
        bool IsColliding(const RectCollider& _other);

        /// <summary>
        /// コライダーを訪問
        /// </summary>
        /// <param name="_visitor">訪問するビジター</param>
        void Accept(ColliderVisitor& _visitor) override
        {
            _visitor.Visit(*this);
        }

        /// <summary>
        /// 他のコライダーとの衝突判定
        /// </summary>
        /// <param name="_other">他のコライダー</param>
        void ColliderWidth(Collider& _other) override
        {
            _other.Accept(*visitor);
        }

        /// <summary>
        /// 移動量の追加
        /// </summary>
        void AddVelocity(const Vector2f& _velocity) override
        {
            colDef->localPos += _velocity;
            baseRect.pos = colDef->localPos;
        }

        void AddVelocity()
        {
            colDef->localPos += velocity;
            baseRect.pos = colDef->localPos;
        }

    private:
        /// <summary>
        /// スイープ矩形を算出
        /// </summary>
        void CalcSweptRect();

        std::unique_ptr<RectColliderVisitor> visitor; // ビジター
        shape::Rect baseRect; // 基本の矩形
        shape::Rect sweptRect; // スイープ矩形
    };
}
