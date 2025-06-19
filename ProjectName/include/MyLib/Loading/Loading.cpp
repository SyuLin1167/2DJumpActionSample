#include <thread>
#include "Loading.h"

namespace task
{
    Loading::Loading()
        : progress()
        , isLoading()
    {
        //処理なし
    }

    Loading::~Loading()
    {
        //処理なし
    }

    void Loading::AddTask(Level _level, std::function<void()> _task)
    {
        //タスク数加算
        taskInfo[Level::END].totalTasks++;
        taskInfo[_level].totalTasks++;

        //タスクを追加する
        taskInfo[_level].tasks.emplace_back(std::async(std::launch::async, [this, _level, _task]() {
            auto& info = taskInfo[_level];
            //DATAレベル以外は前のレベルのタスクが終わるまで待つ
            if (_level != Level::DATA)
            {
                taskInfo[static_cast<Level>(static_cast<int>(_level) - 1)].future.wait();
            }

            //タスク実行
            _task();

            //タスク終了後処理
            taskInfo[Level::END].finishTasks++;
            if (++info.finishTasks == info.totalTasks)
            {
                info.promise.set_value();
            }
        }));
    }

    void Loading::WatchProgress()
    {
        taskInfo[Level::END].tasks.emplace_back(std::async(std::launch::async, [this]() {
            auto& info = taskInfo[Level::END];
            //全タスク終了までループ
            while (info.finishTasks < info.totalTasks)
            {
                progress = static_cast<float>(info.finishTasks) / info.totalTasks;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            progress = 1.0f;
            isLoading = false;
        }));
    }
}
