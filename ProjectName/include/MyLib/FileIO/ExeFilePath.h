#pragma once
#include <Windows.h>
#include <filesystem>

/// <summary>
/// ファイル関連
/// </summary>
namespace file
{
    /// <summary>
    /// 実行ファイルの場所を取得
    /// </summary>
    /// <returns>実行ファイルが存在するディレクトリのパス</returns>
    inline std::filesystem::path GetExeDirectory()
    {
        char buffer[MAX_PATH];
        GetModuleFileNameA(nullptr, buffer, MAX_PATH);
        return std::filesystem::path(buffer).parent_path();
    }
}