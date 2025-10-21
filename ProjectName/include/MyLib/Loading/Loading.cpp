module;
#include <thread>
#include <future>

module MyLib.Loading;

namespace task
{
    Loading::Loading()
        : m_progress(0.0f)
        , m_isLoading()
    {
        // 処理なし
    }

    Loading::~Loading()
    {
        //処理なし
    }

    void Loading::AddTask(Level level, std::function<void()> task)
    {
        // タスク総数加算
        auto& endInfo = m_taskInfo[(int)Level::END];
        endInfo.totalTasks.fetch_add(1);

        // レベル別タスク数加算
        auto& info = m_taskInfo[(int)level];
        info.totalTasks.fetch_add(1);

        // タスクを追加する
        m_taskInfo[level].tasks.emplace_back(std::async(std::launch::async, [this, level, task]() {
            auto& info = m_taskInfo[level];
            // DATAレベル以外は前のレベルのタスクが終わるまで待つ
            if (level != Level::DATA)
            {
                m_taskInfo[static_cast<int>(level) - 1].future.wait();
            }

            // タスク実行
            task();

            // タスク終了総数加算
            auto& endInf = m_taskInfo[(int)Level::END];
            endInf.finishTasks.fetch_add(1);

            // レベル別タスク終了総数加算
            auto& inf = m_taskInfo[(int)level];
            int finish = inf.finishTasks.fetch_add(1) + 1;

            // レベル完了で次のレベルへのシグナル
            if (finish == info.totalTasks.load())
            {
                info.promise.set_value();
            }

            // 全レベル完了でフラグを下す
            if (endInf.finishTasks.load() == endInf.totalTasks.load())
            {
                m_isLoading.store(false);
            }
        }));
    }

    void Loading::WatchProgress()
    {
        // 終了確認用タスク追加
        m_taskInfo[Level::END].tasks.emplace_back(std::async(std::launch::async, [this]() {
            auto& info = m_taskInfo[Level::END];
            while (info.finishTasks < info.totalTasks)
            {
                m_progress = static_cast<float>(info.finishTasks) / info.totalTasks;
            }
            m_progress = 1.0f;
            m_isLoading.store(false);
        }));
    }
}
