# Asset.DivisionGraph

アセット関連 / 分割画像の管理を担当

所属：[assetのAPI解説](../asset.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Asset/DivisionGraph/DivisionGraph.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Asset/DivisionGraph/DivisionGraph.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Asset.DivisionGraph;
import <unordered_map>;
import <string>;
import Asset.AssetBase;

/// <summary>
/// アセット関連
/// </summary>
export namespace asset
{
    /// <summary>
    /// 分割画像の管理を担当
    /// </summary>
    export class DivisionGraph final :public AssetBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        DivisionGraph() :m_divW(32), m_divH(32) {};

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="divW">分割幅(横)</param>
        /// <param name="divH">分割幅(縦)</param>
        DivisionGraph(int divW, int divH) :m_divW(divW), m_divH(divH) {};

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~DivisionGraph();

        /// <summary>
        /// 分割サイズ変更
        /// </summary>
        /// <param name="divW">分割する横幅</param>
        /// <param name="divH">分割する立幅</param>
        void ChangeDivSize(int divW, int divH)
        {
            m_divW = divW;
            m_divH = divH;
        }

        /// <summary>
        /// ハンドル生成
        /// </summary>
        /// <param name="handleName">ハンドル名</param>
        /// <param name="graphName">画像名</param>
        void CreateHandle(std::string handleName, std::string graphName) override;

        /// <summary>
        /// ハンドル生成(非同期)
        /// </summary>
        /// <param name="handleName">ハンドル名</param>
        /// <param name="graphName">画像名</param>
        void CreateHandleAsync(std::string handleName, std::string graphName) override;

        /// <summary>
        /// ハンドル削除
        /// </summary>
        /// <param name="name">削除するハンドル名</param>
        void DeleteHandle(std::string name) override;

        /// <summary>
        /// ハンドル取得
        /// </summary>
        /// <param name="name">取得するハンドル名</param>
        /// <returns>ハンドル</returns>
        int* GetHandle(std::string name) const
        {
            auto it = m_handles.find(name);
            return it == m_handles.end() ? nullptr : (int*)it->second.handle.data();
        };

        /// <summary>
        /// ハンドル取得
        /// </summary>
        /// <param name="name">取得するハンドル名</param>
        /// <param name="num">取得する添え字</param>
        /// <returns>ハンドル</returns>
        int GetHandle(std::string name, size_t index) const
        {
            auto it = m_handles.find(name);
            if (it == m_handles.end() || index >= it->second.handle.size())
            {
                return -1;
            }
            return it->second.handle[index];
        };

        /// <summary>
        /// 分割総数取得
        /// </summary>
        int GetTotalDiv(std::string name) const
        {
            return m_handles.at(name).handle.size();
        }

    private:
        /// <summary>
        /// ハンドル情報
        /// </summary>
        struct Info
        {
            std::vector<int> handle;
        };

        int m_divW;       //分割幅(横)
        int m_divH;       //分割幅(縦)
        std::unordered_map<std::string, Info> m_handles;  //ハンドル群
    };
}
```
