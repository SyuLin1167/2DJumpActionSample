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

        // コピーコンストラクタとコピー代入演算子を削除
        MemMapFile(const MemMapFile&) = delete;
        MemMapFile& operator=(const MemMapFile&) = delete;

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
        char* GetPtr() noexcept { return ptr; };

        /// <summary>
        /// ファイルサイズの取得
        /// </summary>
        /// <returns>ファイルサイズ</returns>
        size_t GetFileSize() const noexcept;

        /// <summary>
        /// ファイルを閉じる
        /// </summary>
        void Close();
    private:
        HANDLE fileHandle;  //ファイルハンドル
        HANDLE mapHandle;   //マッピングハンドル
        char* ptr;      //ポインタ
    };
}
