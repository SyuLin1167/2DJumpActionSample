module;
#include <DxLib.h>
#include <format>
#include <thread>

module Asset.Graph;

import MyLib.FileIO.ExeFilePath;
import MyLib.Loading.LoadingContext;

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

    void Graph::CreateHandle(std::string handleName, std::string graphName)
    {
        auto fpath = file::GetExeDirectory() / std::format("assets/{}", graphName);
        int handle = LoadGraph(fpath.string().c_str());

        // 非同期読み込み中ならタスクに登録
        if (task::LoadingContext::Get())
        {
            task::LoadingContext::Get()->AddTask(task::GRAPH, [&, handleName,handle]() {
                //非同期読み込み完了待ち
                while (CheckHandleASyncLoad(handle))
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
                handles[handleName] = handle;
            });
            return;
        }

        handles[handleName] = handle;
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
