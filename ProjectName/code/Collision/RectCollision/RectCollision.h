#pragma once
#include"Shape/Rect.h"
#include"CollisionBase/CollisionBase.h"

/// <summary>
/// 当たり判定関連
/// </summary>
namespace collision
{
    /// <summary>
    /// 矩形当たり判定
    /// </summary>
    class RectCollision final :public CollisionBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        RectCollision() = default;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_pos">座標</param>
        /// <param name="_size">サイズ</param>
        /// <param name="_velocity">速さ</param>
        RectCollision(Vector2<float>& _pos, Vector2<float>& _size, Vector2<float>& _velocity);

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_rect">矩形</param>
        /// <param name="_velocity">速さ</param>
        RectCollision(shape::Rect _rect, Vector2<float>& _velocity);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~RectCollision() = default;

        /// <summary>
        /// ディスパッチ
        /// </summary>
        /// <param name="_handle">イベント用ハンドル</param>
        /// <param name="_other">対象のコリジョン</param>
        void Dispatch(uint64_t _handle, CollisionBase* _other) override;

        /// <summary>
        /// 自身のベースの矩形
        /// </summary>
        /// <returns>ベースの矩形</returns>
        const shape::Rect MyBaseRect()
        {
            baseRect.pos = pos;
            baseRect.size = size;
            return baseRect;
        }

        /// <summary>
        /// 自身のスイープ矩形
        /// </summary>
        /// <returns>スイープ矩形</returns>
        const shape::Rect SweptRect()
        {
            CalcSweptRect();
            return sweptRect;
        }

        /// <summary>
        /// 当たり判定処理(Map)
        /// </summary>
        /// <param name="_other">Map当たり判定</param>
        /// <param name="_info">判定対象専用の当たり判定情報</param>
        void ColliderWith(MapCollision& _other, TargetColInfo& _info) override;

        /// <summary>
        /// 当たり判定処理(Rect)
        /// </summary>
        /// <param name="_other">Rect当たり判定</param>
        /// <param name="_info">判定対象専用の当たり判定情報
        void ColliderWith(RectCollision& _other, TargetColInfo& _info) override;

        /// <summary>
        /// 差分を算出
        /// </summary>
        /// <param name="_other"></param>
        void CalcDiff(const RectCollision& _other);

        /// <summary>
        /// 判定のための差分の除外
        /// </summary>
        /// <param name="_xx">左判定</param>
        /// <param name="_xy">右判定</param>
        /// <param name="_yx">上判定</param>
        /// <param name="_yy">下判定</param>
        void ExclDiff(bool _xx, bool _xy, bool _yx, bool _yy);

        /// <summary>
        /// 押し戻し処理
        /// </summary>
        void PushBack();

        /// <summary>
        /// 衝突判定(Rect)
        /// </summary>
        /// <param name="_otherRect">他のRect</param>
        /// <returns>衝突しているか</returns>
        bool HasColliderRect(const shape::Rect& _otherRect)
        {
            return sweptRect.Left() < _otherRect.Right() &&
                sweptRect.Right() > _otherRect.Left() &&
                sweptRect.Top() < _otherRect.Bottom() &&
                sweptRect.Bottom() > _otherRect.Top();
        }

        /// <summary>
        /// 速度簡略表示
        /// </summary>
        /// <returns>それぞれの軸に対して-1,0,1での速度表示</returns>
        Vector2<int> SignVelocity()
        {
            return {
                (velocity.x > 0) - (velocity.x < 0),
                (velocity.y > 0) - (velocity.y < 0)
            };
        }

        /// <summary>
        /// 自身の形状
        /// </summary>
        /// <returns>Rect</returns>
        ShapeTag MyShape() const override
        {
            return ShapeTag::RECT;
        }

    private:
        /// <summary>
        /// スイープ矩形の算出
        /// </summary>
        void CalcSweptRect();

        Vector2<float>& pos;      //座標
        Vector2<float>& size;     //サイズ
        Vector2<float>& velocity; //速度
        shape::Rect baseRect;           //ベース矩形
        shape::Rect sweptRect;          //スイープ矩形
        Vector2<float> diffX;     //X軸差分
        Vector2<float> diffY;     //Y軸差分
    };
}
