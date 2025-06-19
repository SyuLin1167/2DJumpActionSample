#pragma once
#include <string>
#include <array>
#include <unordered_map>
#include <string>

/// <summary>
/// オブジェクト関連
/// </summary>
namespace object
{
    /// <summary>
    /// オブジェクトタグ
    /// </summary>
    enum ObjectTag :uint32_t
    {
        NONE = 0,
        MAP = 1 << 0,
        PLAYER = 1 << 1,
        ENEMY = 1 << 2,
    };

    /// <summary>
    /// タグ群
    /// </summary>
    constexpr std::array OBJECT_TAGS
    {
        NONE,
        MAP,
        PLAYER,
        ENEMY,
    };

    /// <summary>
    /// タグから文字列への変換
    /// </summary>
    static const std::unordered_map<uint32_t, std::string> TagToString
    {
        {ObjectTag::NONE,"none"},
        {ObjectTag::MAP,"map"},
        {ObjectTag::PLAYER,"player"},
        {ObjectTag::ENEMY,"enemy"},
    };

    /// <summary>
    /// 文字列からタグへの変換
    /// </summary>
    static const std::unordered_map<std::string, uint32_t> StringToTag
    {
        {"none",ObjectTag::NONE},
        {"map",ObjectTag::MAP},
        {"player",ObjectTag::PLAYER},
        {"enemy",ObjectTag::ENEMY},
    };
}
