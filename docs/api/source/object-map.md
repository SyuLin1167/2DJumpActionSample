# Object.Map

オブジェクト関連 / タイルマップに関する処理を行う

所属：[objectのAPI解説](../object.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Object/Map/Map.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Object/Map/Map.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Object.Map;

import Object.GameObject;
import Object.MapInfo;
import Asset.AssetManager;
import MyLib.Math.Vector2;

export import <vector>;
import <future>;

using json = nlohmann::json;
using namespace math;

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
        ~Map();

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Init() override;

        /// <summary>
        /// シーン所属時の処理(タイルコライダー生成)
        /// </summary>
        void OnAttach() override;

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
        MapInfo m_mapInfo;                  // マップ情報
        std::unordered_map<size_t, std::vector<size_t>> m_mapData;   //マップデータ

        std::pair<size_t, size_t> rangeX;           //描画範囲X
        std::pair<size_t, size_t> rangeY;           //描画範囲Y

        col2d::ColliderID colID;            // コライダーID
        std::shared_future<MapInfo> m_infoFuture;   // MapInfo通知用future
    };
}
```
