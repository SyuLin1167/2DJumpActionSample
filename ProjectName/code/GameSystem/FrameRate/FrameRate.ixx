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
        /// 自身のインスタンスを返す
        /// </summary>
        /// <returns>自身のインスタンス</returns>
        static FrameRate& Instance()
        {
            static FrameRate instance;
            return instance;
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
            return m_deltaTime;
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
