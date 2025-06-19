#pragma once
#include <memory>

/// <summary>
/// システム関連
/// </summary>
namespace gameSystem
{
    /// <summary>
    /// フレームレートの算出
    /// </summary>
    class FrameRate final
    {
    public:
        /// <summary>
        /// デストラクタ
        /// </summary>
        ~FrameRate() = default;

        /// <summary>
        /// インスタンス生成
        /// </summary>
        /// <returns>生成できたかどうか</returns>
        static void CreateInstance();

        /// <summary>
        /// 自身のインスタンスを返す
        /// </summary>
        /// <returns>自身のインスタンス</returns>
        static FrameRate& Self()
        {
            return *frameRate;
        }

        /// <summary>
        /// フレームレートを算出
        /// </summary>
        void CalcFrameRate();

        /// <summary>
        /// デルタタイム取得
        /// </summary>
        /// <returns>デルタタイム</returns>
        const float& GetDeltaTime() const
        {
            return deltaTime;
        }

#ifdef _DEBUG
        /// <summary>
        /// FPS(フレームレート)描画
        /// </summary>
        void DrawFrameRate() const;
#endif // _DEBUG

    private:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        FrameRate();

        /// <summary>
        /// コピー禁止令
        /// </summary>
        FrameRate(const FrameRate&) = delete;

        /// <summary>
        /// 代入禁止令
        /// </summary>
        FrameRate& operator=(const FrameRate&) = delete;

        /// <summary>
        /// コピー禁止令
        /// </summary>
        FrameRate(FrameRate&&) = delete;

        /// <summary>
        /// 代入禁止令
        /// </summary>
        FrameRate& operator=(FrameRate&&) = delete;

        static std::unique_ptr<FrameRate> frameRate;   //自身のインスタンス

        const float MICRO_SEC = 1000000.0f;     //マイクロ秒
        const float FPS_60 = 60.0f;             //60fps

        long long startTime;                    //開始時刻
        long long nowTime;                      //現在時刻
        long long prevTime;                     //1フレーム前の時刻
        float deltaTime;                        //デルタタイム
        float fps;                              //FramePerSecond
        float frameCount;                       //フレームカウント
    };
}

