#include "MemMapFile.h"

namespace file
{
    MemMapFile::MemMapFile()
        :fileHandle(INVALID_HANDLE_VALUE)
        , mapHandle()
        , pointer()
    {
        //処理なし
    }

    MemMapFile::~MemMapFile()
    {
        UnmapViewOfFile(pointer);
        CloseHandle(fileHandle);
        CloseHandle(mapHandle);
    }

    bool MemMapFile::Open(const char* fileName)
    {
        //ファイルハンドルの作成
        fileHandle = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        if (fileHandle == INVALID_HANDLE_VALUE)
        {
            return false;
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
        pointer = (char*)MapViewOfFile(mapHandle, FILE_MAP_READ, 0, 0, 0);
        return true;
    }

    void MemMapFile::GetPtr(void** ptr)
    {
        *ptr = pointer;
    }
}
