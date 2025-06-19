#pragma once

/// <summary>
/// システム関連
/// </summary>
namespace gameSystem
{
    /// <summary>
    /// ライブラリの管理
    /// </summary>
    class Library final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Library();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Library();

        /// <summary>
        /// 初期化成功判定
        /// </summary>
        /// <returns>成功:true|失敗:false</returns>
        const bool InitSuccess() const
        {
            return success;
        }

    private:
        bool success;        //成功状態
    };
}

