#pragma once
#include <unordered_map>
#include<string>

/// <summary>
/// アセット関連
/// </summary>
namespace asset
{
    /// <summary>
    /// アセットの基底クラス
    /// </summary>
    class AssetBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        AssetBase() = default;

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~AssetBase() = default;

        /// <summary>
        /// ハンドル生成
        /// </summary>
        /// <param name="_handleName">ハンドル名</param>
        /// <param name="_graphName">画像名</param>
        virtual void CreateHandle(std::string _handleName, std::string _graphName) = 0;

        /// <summary>
        /// ハンドル削除
        /// </summary>
        /// <param name="_name">削除するハンドル名</param>
        virtual void DeleteHandle(std::string _name) = 0;
    };
}
