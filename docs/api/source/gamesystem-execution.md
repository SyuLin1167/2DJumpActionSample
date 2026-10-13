# GameSystem.Execution

システム関連 / ゲームの実行を行う

所属：[game-systemのAPI解説](../game-system.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/GameSystem/Execution/Execution.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/GameSystem/Execution/Execution.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module GameSystem.Execution;

import <memory>;

// 前方宣言
export namespace scene
{
    class SceneManager;
}

/// <summary>
/// システム関連
/// </summary>
export namespace gameSystem
{
    class Library;

    /// <summary>
    /// ゲームの実行を行う
    /// </summary>
    export class Execution final
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
        std::unique_ptr<class Library> m_library;         //ライブラリ管理のインスタンス
        std::unique_ptr<scene::SceneManager> m_scene;     //シーン管理のインスタンス
    };
}
```
