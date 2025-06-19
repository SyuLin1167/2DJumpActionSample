#include <Dxlib.h>
#include "Library.h"

namespace gameSystem
{
    Library::Library()
        :success(true)
    {
        SetWindowSizeExtendRate(1.0);
        SetMainWindowText("2DGame");

        SetUseDirect3DVersion(DX_DIRECT3D_11);

        if (DxLib_Init())
        {
            DebugBreak();
            success = false;
        }

        SetDrawScreen(DX_SCREEN_BACK);
    }

    Library::~Library()
    {
        DxLib_End();
    }
}
