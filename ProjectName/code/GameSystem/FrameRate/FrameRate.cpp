#include <DxLib.h>
#include "FrameRate.h"

namespace gameSystem
{
    std::unique_ptr<FrameRate> FrameRate::frameRate = nullptr;

    FrameRate::FrameRate()
        : startTime(GetNowHiPerformanceCount())
        , nowTime(startTime)
        , prevTime(startTime)
        , deltaTime()
        , fps(FPS_60)
        , frameCount()
    {
        CalcFrameRate();
    }

    void FrameRate::CreateInstance()
    {
        if (!frameRate)
        {
            frameRate.reset(new FrameRate);
        }
    }

    void FrameRate::CalcFrameRate()
    {
        //デルタタイムを算出
        nowTime = GetNowHiPerformanceCount();
        deltaTime = (nowTime - prevTime) / MICRO_SEC;
        prevTime = nowTime;

        //fps算出
        if (frameCount == FPS_60)
        {
            fps = MICRO_SEC / ((nowTime - startTime) / FPS_60);
            startTime = nowTime;
            frameCount = 0;
        }
        frameCount++;
    }

#ifdef _DEBUG
    void FrameRate::DrawFrameRate() const
    {
        clsDx();
        printfDx("deltaTime: %f", deltaTime);
        printfDx("fps: %3.1f", fps);
    }
#endif // _DEBUG
}