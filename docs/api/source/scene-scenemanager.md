# Scene.SceneManager

シーン関連 / シーンを管理する

所属：[sceneのAPI解説](../scene.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Scene/SceneManager/SceneManager.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Scene/SceneManager/SceneManager.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Scene.SceneManager;

import <memory>;
import <unordered_map>;
import <stack>;
import <variant>;

import Asset.Graph;
export import Scene.SceneBase;

/// <summary>
/// シーン関連
/// </summary>
export namespace scene
{
    // 前方宣言
    export class SceneBase;

    /// <summary>
    /// シーンを管理する
    /// </summary>
    export class SceneManager final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        SceneManager();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~SceneManager() = default;

        /// <summary>
        /// シーンのループ処理
        /// </summary>
        void GameLoop();

    private:
        /// <summary>
        /// シーンの更新処理
        /// </summary>
        void Update();

        /// <summary>
        /// シーンの描画処理
        /// </summary>
        void Draw();

        /// <summary>
        /// シーンの切り替え処理
        /// </summary>
        void ChangeScene();

        std::stack<std::shared_ptr<SceneBase>> m_nowScene;  //現在のシーン
        SceneCmd m_pendingCmd;                              //次フレームに適用するコマンド
        bool m_isRunning;                                   //ゲームループ継続フラグ
    };
}
```
