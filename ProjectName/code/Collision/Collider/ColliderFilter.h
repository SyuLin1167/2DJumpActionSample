#pragma once
#include <cstdint>
#include <vector>

/// <summary>
/// 当たり判定関連
/// </summary>
namespace col2d
{

    /// <summary>
    /// 形状の種類
    /// </summary>
    enum ShapeType : uint32_t
    {
        RECT = 1u << 0,   //矩形
        CIRCLE = 1u << 1,    // 円
        POLY = 1u << 2,   // 多角形
        TILE = 1u << 3,   // タイル
    };

    /// <summary>
    /// 形状の上位ビットを取得
    /// </summary>
    /// <param name="_shapeType">形状の種類</param>
    /// <returns>上位ビット</returns>
    inline uint64_t ShapeHi(uint32_t _shapeType)
    {
        return static_cast<uint64_t>(_shapeType) << 32;
    }

    /// <summary>
    /// キーを生成
    /// </summary>
    /// <param name="_shapeType">形状の種類</param>
    /// <param name="_ownerID">所有者のID</param>
    /// <returns>生成されたキー</returns>
    inline uint64_t MakeKey(uint32_t _shapeType, uint32_t _ownerID)
    {
        return ShapeHi(_shapeType) | static_cast<uint64_t>(_ownerID);
    }

    /// <summary>
    /// 最小の符号付きビットを取得
    /// </summary>
    /// <param name="_value">値</param>
    /// <returns>最小の符号付きビット</returns>
    inline uint32_t LeastSignBit(const uint32_t& _value)
    {
        return _value & (~_value + 1);
    }

    /// <summary>
    /// フィルタ
    /// </summary>
    struct Filter
    {
        uint64_t category; // カテゴリー
        std::vector<uint64_t> masks; // マスク

        /// <summary>
        /// コンストラクタ
        /// </summary>
        Filter() = default;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Filter() = default;

        /// <summary>
        /// マスクを追加
        /// </summary>
        /// <param name="_shape">追加する形状</param>
        /// <param name="_ownerID">追加する所有者ID</param>
        void AddMask(uint32_t _shape, uint32_t _ownerID)
        {
            while (_shape)
            {
                uint32_t leastSignBit = LeastSignBit(_shape);


                // 既に同じマスクが存在するか確認
                if (std::ranges::find(masks, MakeKey(leastSignBit, _ownerID)) != masks.end())
                {
                    _shape &= ~leastSignBit;
                    continue;
                }
                

                // 既に同じ形状のマスクが存在する場合は、所有者IDを追加
                auto it = std::ranges::find_if(masks, 
                    [&leastSignBit](uint64_t mask) { return (mask >> 32) == leastSignBit; });
                if (it != masks.end())
                {
                    *it |= _ownerID;
                    _shape &= ~leastSignBit;
                    continue;
                }

                // 新しいマスクを追加
                masks.push_back(MakeKey(leastSignBit, _ownerID));
                _shape &= ~leastSignBit;
            }
        }

        /// <summary>
        /// マスクを削除
        /// </summary>
        /// <param name="_mask">削除するマスク</param>
        void RemoveMask(const uint32_t& _mask)
        {
            auto it = std::remove(masks.begin(), masks.end(), _mask);
            if (it != masks.end())
            {
                masks.erase(it, masks.end());
            }
        }

        /// <summary>
        /// マスクをクリア
        /// </summary>
        void ClearMasks()
        {
            masks.clear();
        }

        /// <summary>
        /// マスクが含まれているか確認
        /// </summary>
        /// <param name="_mask">確認するマスク</param>
        /// <returns>含まれているかどうか</returns>
        bool HasMask(const uint64_t& _mask) const
        {
            return std::find(masks.begin(), masks.end(), _mask) != masks.end();
        }
    };
}