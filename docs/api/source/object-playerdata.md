# Object.PlayerData

公開モジュールのソース参照。

所属：[objectのAPI解説](../object.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Object/Character/Player/PlayerData.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Object/Character/Player/PlayerData.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
module;
#include <json.hpp>

export module Object.PlayerData;

import MyLib.Math.Vector2;
import AppContext;

using json = nlohmann::json;
using namespace gameSystem;
using namespace math;

export namespace object
{
    export struct PlayerData
    {
        void Input(const json& data)
        {
            size.x = data["sizeX"].get<float>();
            size.y = data["sizeY"].get<float>();
            pos.x = data["posX"].get<float>();
            pos.y = data["posY"].get<float>();
            moveSpeed.x = data["moveSpeedX"].get<float>();
            moveSpeed.y = data["moveSpeedY"].get<float>();
        }

        Vector2f size;
        Vector2f pos;
        Vector2f moveSpeed;
    };
}
```
