export module Asset.DivisionGraph;
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
        struct Info;
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        DivisionGraph() = default;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="divW">分割する横幅</param>
        /// <param name="divH">分割する立幅</param>
        DivisionGraph(int divW, int divH);

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
            divW = divW;
            divH = divH;
        }

        /// <summary>
        /// ハンドル生成
        /// </summary>
        /// <param name="handleName">ハンドル名</param>
        /// <param name="graphName">画像名</param>
        void CreateHandle(std::string handleName, std::string graphName) override;

        /// <summary>
        /// ハンドル削除
        /// </summary>
        /// <param name="_name">削除するハンドル名</param>
        void DeleteHandle(std::string name) override;

        /// <summary>
        /// ハンドル取得
        /// </summary>
        /// <param name="name">取得するハンドル名</param>
        /// <param name="num">取得する添え字</param>
        /// <returns></returns>
        int GetHandle(std::string name, size_t index) const
        {
            return m_handles.at(name).handle[index];
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

        int m_divW;       //分割幅(横)
        int m_divH;       //分割幅(縦)
        std::unordered_map<std::string, Info> m_handles;  //ハンドル群
    };
}
