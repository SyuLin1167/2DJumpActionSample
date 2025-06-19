#pragma once
#include <Windows.h>
#include <memory>
#include"Math/Vector2.h"

using namespace math;

/// <summary>
/// システム関連
/// </summary>
namespace gameSystem
{
    /// <summary>
    /// ウィンドウについての情報
    /// </summary>
    class Window final
    {
    private:
        /// <summary>
        /// ウィンドウ情報
        /// </summary>
        const struct Info
        {
            const Vector2<int> SIZE{ 1920, 1080 };    //ウィンドウサイズ
            const int COLOR_BIT = 32;    //カラービット
        };

    public:
        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Window() = default;

        /// <summary>
        /// インスタンス初期化
        /// </summary>
        static void InitInstance();

        /// <summary>
        /// ウィンドウ情報取得
        /// </summary>
        /// <returns>ウィンドウ情報</returns>
        const static Info* GetWindowData()
        {
            return window->winInfo.get();
        }

    private:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Window();

        static std::unique_ptr<Window> window;        //自身の実体
        std::unique_ptr<Info> winInfo;        //ウィンドウ情報
    };
}

