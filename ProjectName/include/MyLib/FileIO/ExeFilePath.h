#pragma once
#include <Windows.h>
#include <filesystem>

/// <summary>
/// �t�@�C���֘A
/// </summary>
namespace file
{
    /// <summary>
    /// ���s�t�@�C���̏ꏊ���擾
    /// </summary>
    /// <returns>���s�t�@�C�������݂���f�B���N�g���̃p�X</returns>
    inline std::filesystem::path GetExeDirectory()
    {
        char buffer[MAX_PATH];
        GetModuleFileNameA(nullptr, buffer, MAX_PATH);
        return std::filesystem::path(buffer).parent_path();
    }
}