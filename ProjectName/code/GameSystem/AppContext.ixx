export module AppContext;

import <optional>;

export import MyLib.File.FileSystem;
export import Asset.AssetManager;

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
        }

        /// <summary>
        /// 非アクティブ化
        /// </summary>
        static void Deactivate()
        {
            fileSystem.reset();
            assetMgr.reset();
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

    private:
        inline static std::optional<file::FileSystem> fileSystem{};   // ファイルシステムのインスタンス
        inline static std::optional<asset::AssetManager> assetMgr{};   // アセット管理のインスタンス
    };

    using AppCtx = AppContext;
}