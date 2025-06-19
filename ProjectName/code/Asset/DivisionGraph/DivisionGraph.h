#pragma once
#include "AssetBase/AssetBase.h"

/// <summary>
/// アセット関連
/// </summary>
namespace asset
{
    /// <summary>
    /// 分割画像の管理を担当
    /// </summary>
    class DivisionGraph final :public AssetBase
    {
        struct Info;
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        DivisionGraph() = default;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_divW">分割する横幅</param>
        /// <param name="_divH">分割する立幅</param>
        DivisionGraph(int _divW,int _divH);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~DivisionGraph();

        /// <summary>
        /// 分割サイズ変更
        /// </summary>
        /// <param name="_divW">分割する横幅</param>
        /// <param name="_divH">分割する立幅</param>
        void ChangeDivSize(int _divW, int _divH)
        {
            divW = _divW;
            divH = _divH;
        }

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
        /// <param name="_num">取得する添え字</param>
        /// <returns></returns>
        int GetHandle(std::string _name, int _index) const
        {
            return handles.at(_name).handle[_index];
        };

    private:
        /// <summary>
        /// ハンドル情報
        /// </summary>
        struct Info
        {
            int* handle;
            int total;
        };

        int divW;       //分割幅(横)
        int divH;       //分割幅(縦)
        std::unordered_map<std::string, Info> handles;  //ハンドル群
    };
}
