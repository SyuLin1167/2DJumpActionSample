# 06 サウンドを読み込み・再生する

既存Playerの歩行音に加え、Space押下時の単発SEを教材として追加します。ジャンプ成功時だけ鳴る例ではなく、入力確認用の音です。素材の利用条件は[素材確認](../project/credits.md)を参照してください。

## 音を登録する

Player.cppはすでに`Asset.Sound`と`Component.AudioSource`をimportしています。`Player::Player()`へ次を追加します。

```cpp
asset::SoundDef confirm{};
confirm.name = "lesson-confirm";
confirm.soundType = asset::SOUNDTYPE_SE_ONCE;
confirm.volume = 100;
gameSystem::AppCtx::AssetMgr().Fetch<asset::Sound>()
    ->AddSound(confirm, "SE_Confirm.wav");
```

ファイルは既存の`resources/assets/Sounds/SE/SE_Confirm.wav`を参照します。LoadingScene内でコンストラクターが呼ばれるので、音の読み込みをタスクへ登録できます。

## 再生する

Playerはすでに`Init()`でAudioSourceを追加しています。再追加せず、`Player::Update()`へ次を追加します。

```cpp
if (input::KeyStatus::CheckKey(keyType.SPACE, ON_PRESS)) {
    m_compMgr->GetComponent<component::AudioSource>()->Play("lesson-confirm");
}
```

単発SEは複製ハンドルで再生し、終了時に自動削除する実装です。長押し状態を使うと毎フレーム再生を開始してしまうため、`ON_PRESS`を使います。

## 後始末と確認

`Player::~Player()`へ次を追加します。

```cpp
gameSystem::AppCtx::AssetMgr().Fetch<asset::Sound>()->DeleteSound("lesson-confirm");
```

押下1回で1音、長押しで連打にならないことを確認します。ループSEは既存歩行音の`Play`／`Stop`を参照してください。BGMの読み込みと再生・破棄APIの整合性、BGM_ONCEの単発動作は未確認のため完成例に含めません。

次：[シーン切り替え](./scene.md) · 参照：[AudioSource](../api/component.md)
