#include <DxLib.h>
#include "Window.h"

namespace gameSystem
{
    std::unique_ptr<Window> Window::window = nullptr;

    void Window::InitInstance()
    {
        //自身の中身が空だったらインスタンス生成
        if (!window) {
            window.reset(new Window);
        }
    }

    Window::Window()
    {
        winInfo.reset(new Info);

        ChangeWindowMode(true);
        SetGraphMode(winInfo->SIZE.x, winInfo->SIZE.y, winInfo->COLOR_BIT);
    }
}