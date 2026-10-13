# Object.ObjectData

公開モジュールのソース参照。

所属：[objectのAPI解説](../object.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Object/GameObject/ObjectData.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Object/GameObject/ObjectData.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Object.ObjectData;

import MyLib.Math.Vector2;

using namespace math;

export namespace object
{
    export struct InitData
    {
        Vector2f pos;
        Vector2f velocity;
    };
}
```
