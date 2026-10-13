# MyLib.Coroutine

待機時間 / 待機処理

所属：[mylibのAPI解説](../mylib.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/include/MyLib/Coroutine.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/include/MyLib/Coroutine.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module MyLib.Coroutine;
export import <iostream>;
export import <coroutine>;
export import <functional>;
export import <variant>;

/// <summary>
/// 待機時間
/// </summary>
export struct WaitForSeconds
{
    float seconds;                  //待機する秒数
};

/// <summary>
/// 待機処理
/// </summary>
export struct WaitUntil
{
    std::function<bool()> pred;     //待機する処理
};

export using YieldType = std::variant<std::monostate, WaitForSeconds, WaitUntil>;      //co_yieldの待機用variant

/// <summary>
/// コルーチン
/// </summary>
export struct Coroutine
{
    struct promise_type;

    // コピー禁止
    Coroutine(const Coroutine&) = delete;
    Coroutine& operator=(const Coroutine&) = delete;

    //std::moveのみ許可する
    Coroutine(Coroutine&& other) noexcept : handle(other.handle)
    {
        other.handle = nullptr;
    }
    Coroutine& operator=(Coroutine&& other) noexcept
    {
        if (this != &other) {
            if (handle) handle.destroy();
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Coroutine() : handle(nullptr) {};

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="h">作成するcoroutine_handle</param>
    Coroutine(std::coroutine_handle<promise_type> _handle) : handle(_handle) {}

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Coroutine()
    {
        if (handle)
        {
            handle.destroy();
        }
    }

    /// <summary>
    /// コルーチン展開用ルール
    /// </summary>
    struct promise_type
    {
        /// <summary>
        /// 返還オブジェクト取得
        /// </summary>
        /// <returns>Coroutin型オブジェクト</returns>
        Coroutine get_return_object()
        {
            return { std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        /// <summary>
        /// コルーチン開始処理
        /// </summary>
        /// <returns>suspend状態</returns>
        std::suspend_always initial_suspend()
        {
            return {};
        }

        /// <summary>
        /// コルーチン終了処理
        /// </summary>
        /// <returns>suspend状態</returns>
        std::suspend_always final_suspend() noexcept
        {
            return {};
        }

        /// <summary>
        /// co_return呼び出し用
        /// </summary>
        void return_void() {}

        /// <summary>
        /// co_yield呼び出し用
        /// </summary>
        /// <param name="">待機用ルール</param>
        std::suspend_always yield_value(YieldType _yT)
        {
            yieldType = _yT;
            return {};
        }

        /// <summary>
        /// 例外発生時処理
        /// </summary>
        void unhandled_exception()
        {
            throw;
        }

        YieldType yieldType;    //yield状況
    };

    /// <summary>
    /// 1ステップ進める
    /// </summary>
    /// <returns>行進可能状況</returns>
    bool resume() const
    {
        if (!handle || handle.done())
        {
            return false;
        }
        handle.resume();
        return !handle.done();
    }

    /// <summary>
    /// 待機指示の確認
    /// </summary>
    /// <returns>待機指示</returns>
    YieldType get_yield_type() const
    {
        return handle.promise().yieldType;
    }

    std::coroutine_handle<promise_type> handle;     //resume()用ハンドル
};
```
