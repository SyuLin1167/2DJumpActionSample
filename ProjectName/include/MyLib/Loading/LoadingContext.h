#pragma once
#include "Loading.h"

/// <summary>
/// タスク関連
/// </summary>
namespace task
{
    /// <summary>
    /// Loading用スコープコンテキスト
    /// </summary>
    class LoadingContext final
    {
    public:
        /// <summary>
        /// Loadingクラスの確保
        /// </summary>
        /// <param name="_loading">確保するLoading</param>
        static void Set(Loading* _loading)
        {
            current = _loading;
        }

        /// <summary>
        /// Loadingの取得
        /// </summary>
        /// <returns>確保中のLoading</returns>
        static Loading* Get()
        {
            return current;
        }

        /// <summary>
        /// Loadingの解放
        /// </summary>
        static void Release()
        {
            delete current;
        }
    private:
        static inline thread_local Loading* current = nullptr;  //確保中のLoading
    };
}
