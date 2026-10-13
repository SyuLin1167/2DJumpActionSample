# Component.AudioSource

コンポーネント関連 / サウンドを操作するクラス

所属：[componentのAPI解説](../component.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Component/AudioSource/AudioSource.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Component/AudioSource/AudioSource.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Component.AudioSource;

import <string>;
import <unordered_map>;

import Component;
import Asset.SoundDef;
import Object.GameObject;

using namespace asset;

/// <summary>
/// コンポーネント関連
/// </summary>
export namespace component
{
    /// <summary>
    /// サウンドを操作するクラス
    /// </summary>
    export class AudioSource final : public ComponentBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        AudioSource() = default;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="owner">所有者</param>
        AudioSource(object::GameObject* owner);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~AudioSource();

        /// <summary>
        /// 再生
        /// </summary>
        /// <param name="soundName">再生するサウンド</param>
        void Play(const std::string& soundName);

        /// <summary>
        /// 一時停止
        /// </summary>
        /// <param name="soundName">一時停止するサウンド</param>
        void Pause(const std::string& soundName);

        /// <summary>
        /// 停止
        /// </summary>
        /// <param name="soundName">停止するサウンド</param>
        void Stop(const std::string& soundName);

    private:
        std::unordered_map<std::string, SoundState> m_states; // 再生情報群
    };
}
```
