#pragma once
#include <unordered_map>
#include <memory>
#include "KeyTag.h"

constexpr int ON_RELEASE = 0x0001;      //未入力時
constexpr int RELEASING = 0x0002;       //未入力中
constexpr int ON_PRESS = 0x0004;        //入力時
constexpr int PRESSING = 0x0008;        //入力中

/// <summary>
/// 入力関連
/// </summary>
namespace input
{
    /// <summary>
    /// 入力情報の管理
    /// </summary>
    class KeyStatus final
    {
    public:
        /// <summary>
        /// インスタンス初期化
        /// </summary>
        static void InitInstance();

        /// <summary>
        /// キー情報更新
        /// </summary>
        static void UpdateKeyState();

        /// <summary>
        /// キー情報判定
        /// </summary>
        /// <param name="key">対象キー</param>
        /// <param name="state">対象ステータス</param>
        /// <returns>一致:false|不一致:false</returns>
        static bool DecisionKeyState(const int key, const int state);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~KeyStatus() = default;

    private:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        KeyStatus();

        static std::unique_ptr<KeyStatus> keyStatus;    //自身の実体
        std::unordered_map<int, int> keyData;     //キー情報
    };
}