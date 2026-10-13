# Scene.Result

シーン関連 / リザルトシーンを担当

所属：[sceneのAPI解説](../scene.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Scene/Result/Result.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Scene/Result/Result.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Scene.Result;
import Scene.SceneBase;

/// <summary>
/// シーン関連
/// </summary>
export namespace scene
{
    /// <summary>
    /// リザルトシーンを担当
    /// </summary>
    export class Result final : public SceneBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Result();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Result() = default;

        /// <summary>
        ///　初期化処理
        /// </summary>
        void Init() override {}
        
        /// <summary>
        /// 更新処理
        /// </summary>
        /// <returns>次フレーム適用のコマンド</returns>
        SceneCmd Update() override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() override;
    };
}
```
