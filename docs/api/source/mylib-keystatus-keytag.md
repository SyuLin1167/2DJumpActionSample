# MyLib.KeyStatus.KeyTag

ゲームの操作に必要なキー / ループ制御用キー一覧

所属：[mylibのAPI解説](../mylib.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/include/MyLib/KeyStatus/KeyTag.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/include/MyLib/KeyStatus/KeyTag.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
module;
#include <DxLib.h>

export module MyLib.KeyStatus.KeyTag;

import <vector>;
import <memory>;

/// <summary>
/// ゲームの操作に必要なキー
/// </summary>
export constexpr struct KeyType
{
    const int ESCAPE = KEY_INPUT_ESCAPE;    //エスケープキー
    const int E = KEY_INPUT_E;              //Eキー
    const int R = KEY_INPUT_R;              //Rキー
    const int SPACE = KEY_INPUT_SPACE;      //SPACEキー
    const int LEFT = KEY_INPUT_LEFT;        //左キー
    const int RIGHT = KEY_INPUT_RIGHT;      //右キー
}keyType;


/// <summary>
/// ループ制御用キー一覧
/// </summary>
export const std::vector<int> KEYS =
{
    keyType.ESCAPE,
    keyType.E,
    keyType.R,
    keyType.SPACE,
    keyType.LEFT,
    keyType.RIGHT,
};
```
