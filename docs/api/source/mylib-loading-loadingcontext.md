# MyLib.Loading.LoadingContext

タスク関連 / Loading用スコープコンテキスト

所属：[mylibのAPI解説](../mylib.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/include/MyLib/Loading/LoadingContext.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/include/MyLib/Loading/LoadingContext.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module MyLib.Loading.LoadingContext;

export import MyLib.Loading;

/// <summary>
/// タスク関連
/// </summary>
export namespace task
{
    /// <summary>
    /// Loading用スコープコンテキスト
    /// </summary>
    export class LoadingContext final
    {
    public:
        /// <summary>
        /// Loadingクラスの確保
        /// </summary>
        /// <param name="loading">確保するLoading</param>
        static void Set(Loading* loading)
        {
            m_current = loading;
        }

        /// <summary>
        /// Loadingの取得
        /// </summary>
        /// <returns>確保中のLoading</returns>
        static Loading* Get()
        {
            return m_current;
        }

        /// <summary>
        /// Loadingの解放
        /// </summary>
        static void Release()
        {
            delete m_current;
            m_current = nullptr;
        }
    private:
        static inline thread_local Loading* m_current = nullptr;  //確保中のLoading
    };
}
```
