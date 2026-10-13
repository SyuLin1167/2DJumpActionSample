# Asset.Sound

アセット関連 / サウンドを担当するクラス

所属：[assetのAPI解説](../asset.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Asset/Sound/Sound.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Asset/Sound/Sound.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Asset.Sound;

import <memory>;
import <unordered_map>;
import <string>;

import Asset.AssetBase;
import Asset.DivisionGraph;
export import Asset.SoundDef;
import MyLib.Math.Vector2;

/// <summary>
/// アセット関連
/// </summary>
export namespace asset
{
    /// <summary>
    /// サウンドを担当するクラス
    /// </summary>
    export class Sound final :public AssetBase
    {
        // 前方宣言
        struct SoundInfo;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Sound() = default;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Sound();

        /// <summary>
        /// ハンドル生成
        /// </summary>
        /// <param name="soundName">サウンド名</param>
        /// <param name="fileName">ファイル名</param>
        void CreateHandle(std::string soundName, std::string fileName) override;

        /// <summary>
        /// ハンドル生成(非同期)
        /// </summary>
        /// <param name="soundName">サウンド名</param>
        /// <param name="fileName">ファイル名</param>
        void CreateHandleAsync(std::string soundName, std::string fileName) override;

        /// <summary>
        /// サウンド追加
        /// </summary>
        /// <param name="soundDef">サウンド定義</param>
        /// <param name="fileName">ファイル名</param>
        void AddSound(const SoundDef& soundDef, std::string fileName = "");

        /// <summary>
        /// ハンドル削除
        /// </summary>
        /// <param name="name">削除するサウンド名</param>
        void DeleteHandle(std::string soundName) override;

        /// <summary>
        /// サウンド削除
        /// </summary>
        /// <param name="animName">削除するサウンド名</param>
        void DeleteSound(const std::string& soundName);

        /// <summary>
        /// サウンド取得
        /// </summary>
        /// <param name="animName">取得するアニメーション</param>
        /// <returns>取得対象のアニメーション</returns>
        const SoundInfo GetSound(const std::string& soundName) const
        {
            if (m_sounds.find(soundName) != m_sounds.end())
            {
                return m_sounds.at(soundName);
            }
            return {};
        }

    private:
        /// <summary>
        /// サウンド情報
        /// </summary>
        struct SoundInfo
        {
            int handle = -1;    // ハンドル
            SoundDef soundDef;  // サウンド定義
        };
        std::unordered_map<std::string, SoundInfo> m_sounds;  // サウンド群
    };
}
```
