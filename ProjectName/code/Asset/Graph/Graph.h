#pragma once
#include "AssetBase/AssetBase.h"

/// <summary>
/// アセット関連
/// </summary>
namespace asset
{
    /// <summary>
    /// 画像の管理を担当
    /// </summary>
    class Graph final :public AssetBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Graph();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Graph();

        /// <summary>
        /// ハンドル生成
        /// </summary>
        /// <param name="_handleName">ハンドル名</param>
        /// <param name="_graphName">画像名</param>
        void CreateHandle(std::string _handleName, std::string _graphName) override;

        /// <summary>
        /// ハンドル削除
        /// </summary>
        /// <param name="_name">削除するハンドル名</param>
        void DeleteHandle(std::string _name) override;

        /// <summary>
        /// ハンドル取得
        /// </summary>
        /// <param name="_name">取得するハンドル名</param>
        /// <returns>ハンドル</returns>
        int GetHandle(std::string _name) const 
        {
            return  handles.at(_name);
        }
    private:
        std::unordered_map<std::string, int> handles;   //ハンドル群
    };
}

