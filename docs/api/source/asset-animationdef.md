# Asset.AnimationDef

アセット関連 / アニメーションの種類

所属：[assetのAPI解説](../asset.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Asset/Animation/AnimationDef.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Asset/Animation/AnimationDef.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Asset.AnimationDef;

import <string>;
import MyLib.Math.Vector2;

/// <summary>
/// アセット関連
/// </summary>
export namespace asset
{
    /// <summary>
    /// アニメーションの種類
    /// </summary>
    export const enum class AnimType
    {
        LOOP,       // ループ再生
        ONCE,       // 一度だけ再生
        PINGPONG    // 行きと帰りで再生
    };

    /// <summary>
    /// アニメーションの状態
    /// </summary>
    export const enum class AnimState
    {
        PLAY,       // 再生中
        STOP,       // 停止中
        PAUSE,      // 一時停止中
    };

    /// <summary>
    /// アニメーション定義
    /// </summary>
    export struct AnimationDef final
    {
        AnimationDef() = default;
        ~AnimationDef() = default;

        AnimType type = AnimType::LOOP; // アニメーションの種類
        std::string name; // アニメーション名
        float startFrame = 1; // 開始フレーム
        float endFrame; //終了フレーム
        float animationSpeed; // アニメーション速度
        math::Vector2f size; // サイズ
    };
}
```
