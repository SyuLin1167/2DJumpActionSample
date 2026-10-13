# Scene.Play

シーン関連 / プレイシーンを担当

所属：[sceneのAPI解説](../scene.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Scene/Play/Play.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Scene/Play/Play.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Scene.Play;
import Scene.SceneBase;
import MyLib.Math.Vector2;
import Asset.Graph;

/// <summary>
/// シーン関連
/// </summary>
export namespace scene
{
    /// <summary>
    /// プレイシーンを担当
    /// </summary>
    export class Play final :public SceneBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Play();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Play();

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Init() override;

        /// <summary>
        /// 更新処理
        /// </summary>
        SceneCmd Update() override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() override;

    private:
        /// <summary>
        /// スクロール背景描画
        /// </summary>
        /// <param name="parallax">視差効果の強さ（0.0～1.0）</param>
        void DrawScrollingBackground(float parallax = 0.5f);

        bool m_cleared;     // クリアフラグ
    };
}
```
