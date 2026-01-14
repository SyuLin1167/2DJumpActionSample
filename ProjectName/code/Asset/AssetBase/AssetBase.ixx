export module Asset.AssetBase;
import <unordered_map>;
import <string>;

/// <summary>
/// アセット関連
/// </summary>
export namespace asset
{
    /// <summary>
    /// アセットの基底クラス
    /// </summary>
    export class AssetBase
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
        /// <param name="handleName">ハンドル名</param>
        /// <param name="graphName">画像名</param>
        virtual void CreateHandle(std::string handleName, std::string graphName) = 0;

        /// <summary>
        /// ハンドル生成(非同期)
        /// </summary>
        /// <param name="handleName">ハンドル名</param>
        /// <param name="graphName">画像名</param>
        virtual void CreateHandleAsync(std::string handleName, std::string graphName) = 0;

        /// <summary>
        /// ハンドル削除
        /// </summary>
        /// <param name="name">削除するハンドル名</param>
        virtual void DeleteHandle(std::string name) = 0;
    };
}
