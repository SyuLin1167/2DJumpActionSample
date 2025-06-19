#pragma once
#include<functional>
#include <array>
#include"Math/Vector2.h"

using namespace math;

/// <summary>
/// 当たり判定関連
/// </summary>
namespace collision
{
    class MapCollision;
    class RectCollision;

    /// <summary>
    /// 形状タグ
    /// </summary>
    enum ShapeTag :uint32_t
    {
        NONE = 0,                       //なし
        RECT = 1 << 0,                  //矩形
        CIRCLE = 1 << 1,                //円
        MAP = 1 << 2,                   //マップ
    };

    /// <summary>
    /// 形状タグ群
    /// </summary>
    constexpr std::array SHAPE_TAGS
    {
        NONE,
        RECT,
        CIRCLE,
        MAP,
    };

    /// <summary>
    /// 当たり判定の基底クラス
    /// </summary>
    class CollisionBase
    {
    protected:
        /// <summary>
        /// 対象の当たり判定情報
        /// </summary>
        struct TargetColInfo
        {
            bool isTrriger;         //貫通するか
            std::vector<std::function<void()>> events;  //衝突時のイベント
        };

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        CollisionBase();

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~CollisionBase() = default;

        /// <summary>
        /// 自身の形状
        /// </summary>
        /// <returns></returns>
        virtual ShapeTag MyShape() const = 0;

        /// <summary>
        /// 対象の当たり判定を追加
        /// </summary>
        /// <param name="_object">対象のオブジェクト</param>
        /// <param name="_shape">対象の形状</param>
        /// <param name="_event">衝突時のイベント</param>
        /// <param name="_isTrriger">貫通するかどうか</param>
        void AddTargetCollision(uint32_t _object, uint32_t _shape, std::function<void()> _event = nullptr, bool _isTrriger = true);

        /// <summary>
        /// 対象の当たり判定を含んでいるか
        /// </summary>
        /// <param name="_key">判定キー</param>
        /// <returns>含まれるかどうか</returns>
        bool HasTargetCollision(uint64_t _key)
        {
            for (auto& other : targetColInfo)
            {
                if (other.first & _key)
                {
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// ディスパッチ
        /// </summary>
        /// <param name="_handle">情報参照用ハンドル</param>
        /// <param name="_other">対象の当たり判定</param>
        virtual void Dispatch(uint64_t _handle, CollisionBase* _other) = 0;

        /// <summary>
        /// 対象との衝突処理(Map)
        /// </summary>
        /// <param name="_other">Map当たり判定</param>
        /// <param name="_info">当たり判定情報</param>
        virtual void ColliderWith(MapCollision& _other, TargetColInfo& _info) {};

        /// <summary>
        /// 対象との衝突処理(Rect)
        /// </summary>
        /// <param name="_other">Rect当たり判定</param>
        /// <param name="_info">当たり判定情報</param>
        virtual void ColliderWith(RectCollision& _other, TargetColInfo& _info) {};

    protected:
        std::unordered_map<uint64_t, TargetColInfo> targetColInfo;     //判定対象の当たり判定情報
    };
}
