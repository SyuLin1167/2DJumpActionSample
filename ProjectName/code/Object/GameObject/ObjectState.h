#pragma once

/// <summary>
/// オブジェクト関連
/// </summary>
namespace object
{
    /// <summary>
    /// メインステータス
    /// </summary>
    enum MainState :uint32_t
    {
        ACTIVE = 0,           //アクティブ状態
        PAUSE = 1 << 0,       //停止状態
        DEAD = 1 << 1,        //死亡状態
    };
}
