module;
#include <thread>
#include <future>
#include <chrono>

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
        // 処理なし
    }

    void Loading::AddTask(Level level, std::function<void()> task)
    {
        // タスク総数を加算
        auto& endInfo = m_taskInfo[(int)Level::END];
        endInfo.totalTasks.fetch_add(1, std::memory_order_relaxed);

        // レベル別タスク総数を加算
        auto& info = m_taskInfo[(int)level];
        info.totalTasks.fetch_add(1, std::memory_order_relaxed);

        // タスクの追加実行
        m_taskInfo[(int)level].tasks.emplace_back(std::async(std::launch::async, [this, level, task]() {

            // 前レベルの完了待ち
            if (level != Level::DATA)
            {
                int prevIndex = (int)level - 1;
                while (prevIndex >= 0)
                {
                    auto& prev = m_taskInfo[prevIndex];
                    if (prev.totalTasks.load(std::memory_order_acquire) > 0)
                    {
                        prev.future.wait();
                        break;
                    }
                    --prevIndex;
                }
            }

            // タスク実行
            task();

            // 全体レベルの完了数を加算
            auto& endInf = m_taskInfo[(int)Level::END];
            endInf.finishTasks.fetch_add(1, std::memory_order_relaxed);

            // レベル別の完了数を加算
            auto& info = m_taskInfo[(int)level];
            int finish = info.finishTasks.fetch_add(1, std::memory_order_relaxed) + 1;

            // レベル完了でシグナル
            if (finish == info.totalTasks.load(std::memory_order_relaxed))
            {
                info.promise.set_value();
            }

            // 全レベル完了でフラグを下ろす
            if (endInf.finishTasks.load(std::memory_order_relaxed) == endInf.totalTasks.load(std::memory_order_relaxed))
            {
                m_isLoading.store(false, std::memory_order_relaxed);
            }
        }));
    }

    void Loading::WatchProgress()
    {
        // 監視用タスクが未登録なら登録
        if (m_taskInfo[Level::END].tasks.empty())
        {
            // 監視用タスクを追加
            m_taskInfo[Level::END].tasks.emplace_back(std::async(std::launch::async, [this]() {
                auto& info = m_taskInfo[Level::END];
                using namespace std::chrono_literals;

                // 全タスク終了まで進捗を更新
                while (info.finishTasks.load(std::memory_order_relaxed) < info.totalTasks.load(std::memory_order_relaxed))
                {
                    const auto total = std::max(1, info.totalTasks.load(std::memory_order_relaxed));
                    m_progress = static_cast<float>(info.finishTasks.load(std::memory_order_relaxed)) / static_cast<float>(total);
                    std::this_thread::sleep_for(8ms);
                }
                m_progress = 1.0f;
                }));
        }
    }
}
