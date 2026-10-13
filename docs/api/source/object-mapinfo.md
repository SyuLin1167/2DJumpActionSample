# Object.MapInfo

オブジェクト関連 / マップ情報

所属：[objectのAPI解説](../object.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Object/Map/MapInfo.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Object/Map/MapInfo.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
module;
#include <json.hpp>

export module Object.MapInfo;

import MyLib.Math.Vector2;

using json = nlohmann::json;
using namespace math;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    /// <summary>
    /// マップ情報
    /// </summary>
    export struct MapInfo
    {
        Vector2<size_t> mapSize;    // マップサイズ(タイル数)
        Vector2f tileSize; // タイルサイズ(ピクセル数)
        Vector2u chunkSize;               // チャンクサイズ

        /// <summary>
        /// JSONからマップ情報を生成
        /// </summary>
        /// <param name="j">JSONデータ</param>
        /// <returns>マップ情報</returns>
        MapInfo FromJson(const json& j)
        {
            mapSize.x = j.at("width").get<size_t>();
            mapSize.y = j.at("height").get<size_t>();
            tileSize.x = j.at("tilewidth").get<float>();
            tileSize.y = j.at("tileheight").get<float>();
            return *this;
        }
    };
}
```
