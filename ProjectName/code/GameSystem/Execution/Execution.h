#pragma once
#include <memory>

/// <summary>
/// シーン関連(前方宣言)
/// </summary>
namespace scene
{
    class SceneManager;
}

/// <summary>
/// システム関連
/// </summary>
namespace gameSystem
{
    class Library;

    /// <summary>
    /// ゲームの実行を行う
    /// </summary>
    class Execution final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Execution();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Execution();

        /// <summary>
        /// ゲーム実行処理
        /// </summary>
        /// <returns>-1:エラー|0:正常終了</returns>
        int Run();

    private:
        std::unique_ptr<class Library> library;         //ライブラリ管理のインスタンス
        std::unique_ptr<scene::SceneManager> scene;     //シーン管理のインスタンス
    };
}

