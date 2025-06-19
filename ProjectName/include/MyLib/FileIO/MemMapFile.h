#pragma once
#include <Windows.h>
#include <filesystem>
#include "FileIO/ExeFilePath.h"

/// <summary>
/// ファイル関連
/// </summary>
namespace file
{
    /// <summary>
    /// メモリマップファイルに関する処理を行う
    /// </summary>
    class MemMapFile
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        MemMapFile();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~MemMapFile();

        /// <summary>
        /// ファイルを開く(読み込み)
        /// </summary>
        /// <param name="fileName">ファイルパス</param>
        /// <returns>開けたかどうか</returns>
        bool Open(const char* fileName);

        /// <summary>
        /// ファイルポインタの取得
        /// </summary>
        /// <param name="ptr">ポインタ</param>
        void GetPtr(void** ptr);
    private:
        HANDLE fileHandle;  //ファイルハンドル
        HANDLE mapHandle;   //マッピングハンドル
        void* pointer;      //ポインタ
    };
}
