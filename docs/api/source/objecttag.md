# ObjectTag

オブジェクト関連 / オブジェクトタグ

所属：[objectのAPI解説](../object.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Object/GameObject/ObjectTag.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Object/GameObject/ObjectTag.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module ObjectTag;

import <string>;
import <array>;
import <unordered_map>;
import <string>;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    /// <summary>
    /// オブジェクトタグ
    /// </summary>
    export enum ObjectTag :uint32_t
    {
        NONE = 0,
        MAP = 1 << 0,
        PLAYER = 1 << 1,
        ENEMY = 1 << 2,
        GOAL = 1 << 3,
    };

    /// <summary>
    /// タグ群
    /// </summary>
    export constexpr std::array OBJECT_TAGS
    {
        NONE,
        MAP,
        PLAYER,
        ENEMY,
        GOAL,
    };

    /// <summary>
    /// タグから文字列への変換
    /// </summary>
    export const std::unordered_map<uint32_t, std::string> TagToString
    {
        {ObjectTag::NONE,"none"},
        {ObjectTag::MAP,"map"},
        {ObjectTag::PLAYER,"player"},
        {ObjectTag::ENEMY,"enemy"},
        {ObjectTag::GOAL,"goal"},
    };

    /// <summary>
    /// 文字列からタグへの変換
    /// </summary>
    export const std::unordered_map<std::string, uint32_t> StringToTag
    {
        {"none",ObjectTag::NONE},
        {"map",ObjectTag::MAP},
        {"player",ObjectTag::PLAYER},
        {"enemy",ObjectTag::ENEMY},
        {"goal",ObjectTag::GOAL},
    };
}
```
