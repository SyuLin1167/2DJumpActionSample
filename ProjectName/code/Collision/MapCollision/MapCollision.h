#pragma once
#include<string>
#include<vector>
#include<unordered_map>
#include"CollisionBase/CollisionBase.h"
#include"Shape/Rect.h"

/// <summary>
/// 当たり判定関連
/// </summary>
namespace collision
{
    /// <summary>
    /// マップ当たり判定
    /// </summary>
    class MapCollision final : public CollisionBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        MapCollision() = default;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_fileName">当たり判定ファイル名</param>
        MapCollision(std::string _fileName);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~MapCollision() = default;

        /// <summary>
        /// ディスパッチ(未使用)
        /// </summary>
        void Dispatch(uint64_t _handle, CollisionBase* _other) override {};

        /// <summary>
        /// 対象との衝突処理(Rect)
        /// </summary>
        /// <param name="_other">Rect当たり判定</param>
        /// <param name="_info">当たり判定情報</param>
        void ColliderWith(RectCollision& _other, TargetColInfo& _info) override;

        /// <summary>
        /// 衝突処理
        /// </summary>
        void HandlingCollision(RectCollision& _other, TargetColInfo& _info);

        /// <summary>
        /// 自身の形状
        /// </summary>
        /// <returns>Map</returns>
        ShapeTag MyShape() const override
        {
            return ShapeTag::MAP;
        }

    private:
        /// <summary>
        /// マップデータ構築
        /// </summary>
        /// <param name="ptr">ファイルポインタ</param>
        void CreateMapData(char* ptr);

        /// <summary>
        /// 隣接するブロックがあるか調査
        /// </summary>
        void SurveyAdjacentBlock(size_t x, size_t y);

        /// <summary>
        /// ブロック情報取得
        /// </summary>
        /// <param name="x">インデックス座標X</param>
        /// <param name="y">インデックス座標Y</param>
        /// <returns>指定のブロック情報</returns>
        size_t GetBlockInfo(size_t x, size_t y);

        std::vector<std::vector<size_t>> colData;   //マップチップ当たり判定データ
        shape::Rect colRect;            //判定用矩形
        int8_t boxFlag;                 //隣接用Boxフラグ
        std::pair<int, int> rangeX;     //X軸の判定範囲
        std::pair<int, int> rangeY;     //Y軸の判定範囲
    };
}
