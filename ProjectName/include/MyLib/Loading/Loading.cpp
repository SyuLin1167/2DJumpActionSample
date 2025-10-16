module;
#include <thread>
#include <future>

module MyLib.Loading;

namespace task
{
    Loading::Loading()
        : m_progress()
        , m_isLoading()
    {
        //処理なし
    }

    Loading::~Loading()
    {
        //処理なし
    }

    void Loading::AddTask(Level level, std::function<void()> task)
    {
        //タスク数加算
        m_taskInfo[Level::END].totalTasks++;
        m_taskInfo[level].totalTasks++;

        //タスクを追加する
        m_taskInfo[level].tasks.emplace_back(std::async(std::launch::async, [this, level, task]() {
            auto& info = m_taskInfo[level];
            //DATAレベル以外は前のレベルのタスクが終わるまで待つ
            if (level != Level::DATA)
            {
                m_taskInfo[static_cast<Level>(static_cast<int>(level) - 1)].future.wait();
            }

            //タスク実行
            task();

            //タスク終了後処理
            m_taskInfo[Level::END].finishTasks++;
            if (++info.finishTasks == info.totalTasks)
            {
                info.promise.set_value();
            }
        }));
    }

    void Loading::WatchProgress()
    {
        m_taskInfo[Level::END].tasks.emplace_back(std::async(std::launch::async, [this]() {
            auto& info = m_taskInfo[Level::END];
            //全タスク終了までループ
            while (info.finishTasks < info.totalTasks)
            {
                m_progress = static_cast<float>(info.finishTasks) / info.totalTasks;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            m_progress = 1.0f;
            m_isLoading = false;
        }));
    }
}
