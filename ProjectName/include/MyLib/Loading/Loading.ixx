module;
#include <functional>
#include <future>
#include <atomic>

export module MyLib.Loading;

import <memory>;
import <unordered_map>;
import <array>;
import <vector>;

/// <summary>
/// タスク関連
/// </summary>
export namespace task
{
    /// <summary>
    /// 読み込みレベル
    /// </summary>
    export enum Level :int16_t
    {
        DATA,   // データ読み込み
        INIT,   // 初期化
        GRAPH,  // グラフィック
        SOUND,  // サウンド
        FINAL,  // 最終調整
        END,    // レベル終了マーカー
    };

    /// <summary>
    /// ローディングに関する機能(非同期)
    /// </summary>
    export class Loading final
    {
    public:

        struct Info
        {
            std::atomic<int> totalTasks{ 0 };   // 総タスク数
            std::atomic<int> finishTasks{ 0 };  // 終了タスク数
            std::promise<void> promise;         // このレベルの完了シグナル通知用
            std::shared_future<void> future;    // 他レベル完了待機用共有フューチャ
            std::vector<std::future<void>> tasks;   // タスク群

            /// <summary>
            /// コンストラクタ
            /// </summary>
            Info() : future(promise.get_future().share()) {}

            /// <summary>
            /// リセット
            /// </summary>
            void Reset()
            {
                totalTasks.store(0, std::memory_order_relaxed);
                finishTasks.store(0, std::memory_order_relaxed);
                promise = std::promise<void>();
                future = promise.get_future().share();
                tasks.clear();
            }
        };

        /// <summary>
        /// コンストラクタ
        /// </summary>
        Loading();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Loading();

        /// <summary>
        /// ローディング開始
        /// </summary>
        void StartLoading()
        {
            m_isLoading.store(true, std::memory_order_relaxed);
            for (auto& info : m_taskInfo)
            {
                info.Reset();
            }
            m_progress = 0.0f;
            WatchProgress();
        }

        /// <summary>
        /// タスクの追加
        /// </summary>
        /// <param name="level">読み込みレベル</param>
        /// <param name="task">追加するタスク</param>
        void AddTask(Level level, std::function<void()> task);

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
            return m_isLoading.load(std::memory_order_relaxed);
        }

        /// <summary>
        /// 現在の進捗度
        /// </summary>
        /// <returns>進捗度</returns>
        float NowProgress() const
        {
            auto total = m_taskInfo[(int)Level::END].totalTasks.load();
            auto done = m_taskInfo[(int)Level::END].finishTasks.load();
            return (total == 0) ? 1.0f : float(done) / float(total);
        }

    private:
        std::atomic<bool> m_isLoading;                         //ローディング状況
        std::array<Info, (int)Level::END + 1> m_taskInfo;   //タスク
        float m_progress;                         //進捗度
    };
}

