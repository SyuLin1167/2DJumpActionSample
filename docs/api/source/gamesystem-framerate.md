# GameSystem.FrameRate

システム関連 / フレームレートの算出

所属：[game-systemのAPI解説](../game-system.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/GameSystem/FrameRate/FrameRate.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/GameSystem/FrameRate/FrameRate.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module GameSystem.FrameRate;

import <memory>;

/// <summary>
/// システム関連
/// </summary>
export namespace gameSystem
{
    /// <summary>
    /// フレームレートの算出
    /// </summary>
    export class FrameRate final
    {
    public:
        /// <summary>
        /// コピー禁止令
        /// </summary>
        FrameRate(const FrameRate&) = delete;
        FrameRate(FrameRate&&) = delete;

        /// <summary>
        /// 代入禁止令
        /// </summary>
        FrameRate& operator=(const FrameRate&) = delete;
        FrameRate& operator=(FrameRate&&) = delete;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~FrameRate() = default;

        /// <summary>
        /// フレームレートを算出
        /// </summary>
        static void CalcFrameRate()
        {
            Instance().CalcFrameRateImpl();
        }

        /// <summary>
        /// デルタタイム取得
        /// </summary>
        /// <returns>デルタタイム</returns>
        static const float& GetDeltaTime()
        {
            return Instance().m_deltaTime;
        }

#ifdef _DEBUG
        /// <summary>
        /// FPS(フレームレート)描画
        /// </summary>
        static void DrawFrameRate();
#endif // _DEBUG

    private:
        /// <summary>
        /// 自身のインスタンスを返す
        /// </summary>
        /// <returns>自身のインスタンス</returns>
        static FrameRate& Instance()
        {
            static FrameRate instance;
            return instance;
        }

        /// <summary>
        /// コンストラクタ
        /// </summary>
        FrameRate();

        void CalcFrameRateImpl();

        inline static constexpr float MICRO_SEC = 1000000.0f;     //マイクロ秒
        inline static constexpr float FPS_60 = 60.0f;             //60fps

        long long m_startTime;                    //開始時刻
        long long m_nowTime;                      //現在時刻
        long long m_prevTime;                     //1フレーム前の時刻
        float m_deltaTime;                        //デルタタイム
        float m_fps;                              //FramePerSecond
        float m_frameCount;                       //フレームカウント
    };
}
```
