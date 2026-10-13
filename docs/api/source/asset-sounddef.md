# Asset.SoundDef

アセット関連 / サウンドの状態

所属：[assetのAPI解説](../asset.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Asset/Sound/SoundDef.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Asset/Sound/SoundDef.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Asset.SoundDef;

import <string>;

/// <summary>
/// アセット関連
/// </summary>
export namespace asset
{
    export constexpr int8_t SOUNDTYPE_BGM_LOOP = 0x0001;    // BGM(ループ)
    export constexpr int8_t SOUNDTYPE_SE_LOOP = 0x0002;     // SE(ループ)
    export constexpr int8_t SOUNDTYPE_BGM_ONCE = 0x0004;    // BGM
    export constexpr int8_t SOUNDTYPE_SE_ONCE = 0x0008;     // SE

    /// <summary>
    /// サウンドの状態
    /// </summary>
    export const enum class SoundState
    {
        PLAY,       // 再生中
        STOP,       // 停止中
        PAUSE,      // 一時停止中
    };

    /// <summary>
    /// サウンド定義
    /// </summary>
    export struct SoundDef final
    {
        SoundDef() = default;
        ~SoundDef() = default;

        int8_t soundType;        // サウンドの種類
        int8_t playType;        // 再生タイプ
        std::string name;       // サウンド名
        int volume;             // 個別ボリューム
    };
}
```
