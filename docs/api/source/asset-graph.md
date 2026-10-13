# Asset.Graph

アセット関連 / 画像の管理を担当

所属：[assetのAPI解説](../asset.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Asset/Graph/Graph.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Asset/Graph/Graph.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Asset.Graph;
import <unordered_map>;
import <string>;
import Asset.AssetBase;

/// <summary>
/// アセット関連
/// </summary>
export namespace asset
{
    /// <summary>
    /// 画像の管理を担当
    /// </summary>
    export class Graph final :public AssetBase
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
        int GetHandle(const std::string& name) const
        {
            if (auto it = handles.find(name); it != handles.end())
            {
                return it->second;
            }
            return -1;
        }
    private:
        std::unordered_map<std::string, int> handles;   //ハンドル群
    };
}
```
