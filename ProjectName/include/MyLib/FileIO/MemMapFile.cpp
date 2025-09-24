#include "MemMapFile.h"

namespace file
{
    MemMapFile::MemMapFile()
        :fileHandle(INVALID_HANDLE_VALUE)
        , mapHandle()
        , ptr()
    {
        //処理なし
    }

    MemMapFile::~MemMapFile()
    {
        Close();
    }

    bool MemMapFile::Open(const char* fileName)
    {
        Close();

        //ファイルハンドルの作成
        fileHandle = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        if (fileHandle == INVALID_HANDLE_VALUE)
        {
            return false;
        }

        // サイズ0のファイルは MapViewできないので特別扱い
        if (GetFileSize() == 0) {
            mapHandle = nullptr;
            ptr = nullptr;
            return true;
        }

        //ハンドルのマッピング
        mapHandle = CreateFileMapping(fileHandle, 0, PAGE_READONLY, 0, 0, 0);
        if (!mapHandle)
        {
            CloseHandle(fileHandle);
            fileHandle = INVALID_HANDLE_VALUE;
            return false;
        }

        //マッピングデータをポインタへ格納
        ptr = static_cast<char*>(MapViewOfFile(mapHandle, FILE_MAP_READ, 0, 0, 0));
        return true;
    }

    size_t MemMapFile::GetFileSize() const noexcept
    {
        if (fileHandle != INVALID_HANDLE_VALUE)
        {
            LARGE_INTEGER li{};
            if (GetFileSizeEx(fileHandle, &li))
            {
                return static_cast<size_t>(li.QuadPart);
            }
        }
        return 0;
    }

    void MemMapFile::Close()
    {
        if (ptr)
        {
            UnmapViewOfFile(ptr);
            ptr = nullptr;
        }
        if (mapHandle)
        {
            CloseHandle(mapHandle);
            mapHandle = nullptr;
        }
        if (fileHandle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(fileHandle);
            fileHandle = INVALID_HANDLE_VALUE;
        }
    }
}
