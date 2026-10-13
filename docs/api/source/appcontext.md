# AppContext

オブジェクト関連 / 共有コンテキスト

所属：[game-systemのAPI解説](../game-system.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/GameSystem/AppContext.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/GameSystem/AppContext.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module AppContext;

import <optional>;

export import MyLib.File.FileSystem;
export import Asset.AssetManager;
export import UI.UIManager;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace gameSystem
{
    /// <summary>
    /// 共有コンテキスト
    /// </summary>
    export struct AppContext final
    {
        /// <summary>
        /// アクティブ化
        /// </summary>
        static void Activate()
        {
            fileSystem.emplace();
            assetMgr.emplace();
            uiMgr.emplace();
        }

        /// <summary>
        /// 非アクティブ化
        /// </summary>
        static void Deactivate()
        {
            fileSystem.reset();
            assetMgr.reset();
            uiMgr.reset();
        }

        /// <summary>
        /// ファイルシステムのインスタンスを返す
        /// </summary>
        /// <returns>ファイルシステムのインスタンス</returns>
        static file::FileSystem& FileSystem()
        {
            return *fileSystem;
        }

        /// <summary>
        /// アセット管理のインスタンスを返す
        /// </summary>
        /// <returns>アセット管理のインスタンス</returns>
        static asset::AssetManager& AssetMgr()
        {
            return *assetMgr;
        }

        /// <summary>
        /// UI管理のインスタンスを返す
        /// </summary>
        /// <returns>UI管理のインスタンス</returns>
        static ui::UIManager& UIMgr()
        {
            return *uiMgr;
        }

    private:
        inline static std::optional<file::FileSystem> fileSystem{};     // ファイルシステムのインスタンス
        inline static std::optional<asset::AssetManager> assetMgr{};    // アセット管理のインスタンス
        inline static std::optional<ui::UIManager> uiMgr{};             // UI管理のインスタンス
    };

    using AppCtx = AppContext;
}
```
