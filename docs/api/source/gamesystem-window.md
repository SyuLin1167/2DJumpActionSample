# GameSystem.Window

システム関連 / ウィンドウの管理

所属：[game-systemのAPI解説](../game-system.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/GameSystem/Window/Window.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/GameSystem/Window/Window.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module GameSystem.Window;

import <memory>;

import MyLib.Math.Vector2;

using namespace math;

/// <summary>
/// システム関連
/// </summary>
export namespace gameSystem
{
    /// <summary>
    /// ウィンドウの管理
    /// </summary>
    export class Window final
    {
        struct Info;

    public:
        /// <summary>
        /// コピー禁止令
        /// </summary>
        Window(const Window&) = delete;
        Window(Window&&) = delete;

        /// <summary>
        /// 代入禁止令
        /// </summary>
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        /// <summary>
        /// 初期化処理
        /// </summary>
        static void Init()
        {
            Instance();
        }

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Window() = default;

        /// <summary>
        /// ウィンドウ情報取得
        /// </summary>
        /// <returns>ウィンドウ情報</returns>
        static const Info* GetWindowData()
        {
            return Instance().m_winInfo.get();
        }

    private:
        /// <summary>
        /// インスタンスを返す
        /// </summary>
        /// <returns>自身のインスタンス</returns>
        static Window& Instance()
        {
            static Window instance;
            return instance;
        }

        /// <summary>
        /// コンストラクタ
        /// </summary>
        Window();

        /// <summary>
        /// ウィンドウ情報
        /// </summary>
        const struct Info
        {
            const Vector2<uint32_t> SIZE{ 1920, 1080 };    //ウィンドウサイズ
            const int COLOR_BIT = 32;    //カラービット
        };

        std::unique_ptr<Info> m_winInfo;        //ウィンドウ情報
    };
}
```
