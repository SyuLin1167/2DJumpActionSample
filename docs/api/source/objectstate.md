# ObjectState

オブジェクト関連 / メインステータス

所属：[objectのAPI解説](../object.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Object/GameObject/ObjectState.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Object/GameObject/ObjectState.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module ObjectState;
import <cstdint>;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    /// <summary>
    /// メインステータス
    /// </summary>
    export enum MainState :uint32_t
    {
        ACTIVE = 0,           //アクティブ状態
        PAUSE = 1 << 0,       //停止状態
        DEAD = 1 << 1,        //死亡状態
    };
}
```
