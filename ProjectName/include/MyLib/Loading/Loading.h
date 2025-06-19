#pragma once
#include <memory>
#include <unordered_map>
#include <array>
#include <vector>
#include <functional>
#include <future>
#include <atomic>

/// <summary>
/// タスク関連
/// </summary>
namespace task
{
    /// <summary>
    /// 読み込みレベル
    /// </summary>
    enum Level :int16_t
    {
        DATA,
        GRAPH,
        SOUND,
        INIT,
        END,
    };

    /// <summary>
    /// ローディングに関する機能(非同期)
    /// </summary>
    class Loading final
    {
    public:

        struct Info
        {
            std::atomic<int> totalTasks;
            std::atomic<int> finishTasks;//終了タスク
            std::promise<void> promise;
            std::shared_future<void> future = promise.get_future().share();
            std::vector<std::future<void>> tasks;
        };

        /// <summary>
        /// コンストラクタ
        /// </summary>
        Loading();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Loading();

        void StartLoading()
        {
            isLoading = true;
        }

        /// <summary>
        /// タスクの追加
        /// </summary>
        /// <param name="_level">読み込みレベル</param>
        /// <param name="_task">追加するタスク</param>
        void AddTask(Level _level, std::function<void()> _task);

        /// <summary>
        /// 進捗度の監視
        /// </summary>
        void WatchProgress();

        /// <summary>
        /// ローディング中かどうか
        /// </summary>
        /// <returns>ローディング状況</returns>
        bool IsLoading() const
        {
            return isLoading;
        }

        /// <summary>
        /// 現在の進捗度
        /// </summary>
        /// <returns>進捗度</returns>
        float NowProgress() const
        {
            return progress;
        }

    private:
        bool isLoading;                         //ローディング状況
        std::unordered_map<Level, Info> taskInfo;   //タスク
        float progress;                         //進捗度
    };
}

