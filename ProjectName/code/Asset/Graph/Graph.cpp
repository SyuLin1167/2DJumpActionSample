#include <DxLib.h>
#include <format>
#include "Graph.h"
#include "FileIO/ExeFilePath.h"

namespace asset
{
    Graph::Graph()
        :handles()
    {
        //処理なし
    }

    Graph::~Graph()
    {
        //確保した画像の解放
        for (auto& handle : handles)
        {
            DeleteGraph(handle.second);
        }
    }

    void Graph::CreateHandle(std::string _handleName, std::string _graphName)
    {
        auto fpath = file::GetExeDirectory() / std::format("assets/{}", _graphName);
        int handle = LoadGraph(fpath.string().c_str());
        if (handle)
        {
            handles[_handleName] = handle;
        }
    }

    void Graph::DeleteHandle(std::string _name)
    {
        //対象のハンドルを見つけて削除
        auto it = handles.find(_name);
        if (it != handles.end())
        {
            DeleteGraph(it->second);
            handles.erase(it);
        }
    }
}
