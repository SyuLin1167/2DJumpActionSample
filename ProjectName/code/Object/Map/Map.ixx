export module Object.Map;

import Object.GameObject;
import Asset.AssetManager;

export import <vector>;
import <json.hpp>;

using json = nlohmann::json;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    /// <summary>
    /// タイルマップに関する処理を行う
    /// </summary>
    export class Map final :public GameObject
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Map();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Map() = default;

        /// <summary>
        ///  参照するオブジェクト取得
        /// </summary>
        void GetReferenceObject(std::function<std::vector<std::shared_ptr<GameObject>>(uint32_t)> referenceObj) override;

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Init() override;

        /// <summary>
        /// 描画
        /// </summary>
        void Draw() override;

        /// <summary>
        /// 描画範囲算出
        /// </summary>
        /// <param name="pos">座標</param>
        /// <param name="range">範囲</param>
        /// <param name="length">限界範囲</param>
        void CalcDrawRange(int pos, std::pair < size_t, size_t>& range, size_t length);

        /// <summary>
        /// 自身のタグ
        /// </summary>
        /// <returns>Map</returns>
        ObjectTag MyObjectTag() const override
        {
            return ObjectTag::MAP;
        }

    private:
        /// <summary>
        /// マップデータ構築
        /// </summary>
        /// <param name="ptr">ファイルポインタ</param>
        void CreateMapData(char* ptr);

        char* filePtr;                              //ファイルポインタ
        std::vector<std::vector<size_t>> mapData;   //マップデータ
        json mapInfo;   //マップ情報

        std::pair<size_t, size_t> rangeX;           //描画範囲X
        std::pair<size_t, size_t> rangeY;           //描画範囲Y

        GameObject* player;                         //プレイヤー
    };
}
