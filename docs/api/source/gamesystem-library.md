# GameSystem.Library

システム関連 / ライブラリの管理

所属：[game-systemのAPI解説](../game-system.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/GameSystem/Library/Library.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/GameSystem/Library/Library.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module GameSystem.Library;

/// <summary>
/// システム関連
/// </summary>
export namespace gameSystem
{
    /// <summary>
    /// ライブラリの管理
    /// </summary>
    export class Library final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Library();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Library();

        /// <summary>
        /// 初期化成功判定
        /// </summary>
        /// <returns>成功:true|失敗:false</returns>
        const bool InitSuccess() const
        {
            return m_success;
        }

    private:
        bool m_success;        //成功状態
    };
}
```
