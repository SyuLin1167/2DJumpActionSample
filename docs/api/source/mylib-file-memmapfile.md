# MyLib.File.MemMapFile

ファイル関連 / メモリマップファイルに関する処理を行う

所属：[mylibのAPI解説](../mylib.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/include/MyLib/FileSystem/FileIO/MemMapFile.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/include/MyLib/FileSystem/FileIO/MemMapFile.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
module;
#include <Windows.h>
#include <filesystem>

export module MyLib.File.MemMapFile;

/// <summary>
/// ファイル関連
/// </summary>
export namespace file
{
    /// <summary>
    /// メモリマップファイルに関する処理を行う
    /// </summary>
    export class MemMapFile
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        MemMapFile();

        // コピー不可
        MemMapFile(const MemMapFile&) = delete;
        MemMapFile& operator=(const MemMapFile&) = delete;

        // ムーブ可
        MemMapFile(MemMapFile&&) noexcept;
        MemMapFile& operator=(MemMapFile&&) noexcept;

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
        char* GetPtr() noexcept { return m_ptr; };
        const char* GetPtr() const noexcept { return m_ptr; };

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
        HANDLE m_fileHandle;  //ファイルハンドル
        HANDLE m_mapHandle;   //マッピングハンドル
        char* m_ptr;      //ポインタ
    };
}
```
