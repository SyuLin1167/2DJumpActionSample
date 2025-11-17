module;
#include <DxLib.h>
#include <format>
#include <future>
#include <thread>
#include <filesystem>

module Asset.Graph;

import MyLib.Loading.LoadingContext;
import AppContext;

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
        // 以前のハンドルを削除
        DeleteHandle(handleName);

        // グラフィック読み込み
        auto fpath = gameSystem::AppCtx::FileSystem().Resolve(std::format("assets://{}", graphName));
        int handle = LoadGraph(fpath.string().c_str());

        handles[handleName] = handle;
    }

    void Graph::CreateHandleAsync(std::string handleName, std::string graphName)
    {
        // 以前のハンドルを削除
        DeleteHandle(handleName);

        // 非同期タスクを作成
        auto fpath = gameSystem::AppCtx::FileSystem().Resolve(std::format("assets://{}", graphName));

        // グラフィック読み込み
        int handle = LoadGraph(fpath.string().c_str());

        auto task = [this, handle, handleName]()
            {
                while (CheckHandleASyncLoad(handle))
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
                handles[handleName] = handle;
            };

        // 非同期読み込み中ならタスクに登録
        if (task::LoadingContext::Get())
        {
            task::LoadingContext::Get()->AddTask(task::GRAPH, task);
        }
        else
        {
            task();
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
