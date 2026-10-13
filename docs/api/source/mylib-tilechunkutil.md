# MyLib.TileChunkUtil

タイルチャンクキー作成 / ローカルインデックス算出

所属：[mylibのAPI解説](../mylib.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/include/MyLib/TileChunkUtil.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/include/MyLib/TileChunkUtil.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module MyLib.TileChunkUtil;

import <cstdint>;
import <unordered_map>;
import <vector>;
import <optional>;
import MyLib.Math.Vector2;

using namespace math;

export namespace tile
{
    /// <summary>
    /// タイルチャンクキー作成
    /// </summary>
    /// <param name="cx">チャンクX座標</param>
    /// <param name="cy">チャンクY座標</param>
    /// <returns>タイルチャンクキー</returns>
    inline size_t MakeTileKey(uint32_t cx, uint32_t cy)
    {
        return (static_cast<uint64_t>(cy) << 32) | static_cast<uint64_t>(cx);
    }

    /// <summary>
    /// ローカルインデックス算出
    /// </summary>
    /// <param name="x">グリッドX座標</param>
    /// <param name="y">グリッドY座標</param>
    /// <param name="chunkSize">チャンクサイズ</param>
    /// <returns>ローカルインデックス</returns>
    inline size_t LocalIndex(size_t x, size_t y, const Vector2u& chunkSize)
    {
        return (y % chunkSize.y) * chunkSize.x + (x % chunkSize.x);
    }

    /// <summary>
    /// チャンク化されたグリッド構築
    /// </summary>
    /// <typeparam name="T">データ型</typeparam>
    /// <typeparam name="Provider">データ提供関数型</typeparam>
    /// <param name="width">グリッド幅</param>
    /// <param name="height">グリッド高さ</param>
    /// <param name="chunkSize">チャンクサイズ</param>
    /// <param name="provider">データ提供関数</param>
    template<class T, class Provider>
    std::unordered_map<size_t, std::vector<T>> BuildChunkedGrid(size_t width, size_t height, const Vector2u& chunkSize, Provider&& provider)
    {
        std::unordered_map<size_t, std::vector<T>> result;

        for (size_t y = 0; y < height; ++y)
        {
            for (size_t x = 0; x < width; ++x)
            {
                // チャンク座標算出
                const uint32_t cx = static_cast<uint32_t>(x / chunkSize.x);
                const uint32_t cy = static_cast<uint32_t>(y / chunkSize.y);

                // キーとインデックス生成
                const size_t key = MakeTileKey(cx, cy);
                const size_t index = LocalIndex(x, y, chunkSize);
                
                
                std::optional<T> val = provider(x, y, y * width + x, key, index);
                if (!val) continue;

                auto& vec = result[key];
                if (vec.empty())
                {
                    vec.resize(chunkSize.x * chunkSize.y);
                }
                vec[index] = std::move(*val);
            }
        }
        return result;
    }
}
```
