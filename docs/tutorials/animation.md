# 05 アニメーションを切り替える

既存Playerでは、画像の分割・定義を`asset::Animation`、再生状態と描画を`component::Animator`が担当します。この章は既存コードを追う実習です。

## 読み込みと定義

PlayerのコンストラクターはLoadingSceneの中で呼ばれ、画像読み込みを登録します。

```cpp
gameSystem::AppCtx::AssetMgr().Fetch<asset::Animation>()
    ->CreateHandleAsync("Player", "player.png", pData.size.x, pData.size.y);
```

読み込み完了後の`Init()`で待機・歩行の定義を登録します。既存の設定は次の形です。

```cpp
asset::AnimationDef idle{};
idle.name = AssetName::IDLE;
idle.type = asset::AnimType::LOOP;
idle.animationSpeed = 4;
idle.endFrame = 4;
idle.size = pData.size;
auto walk = idle;
walk.name = AssetName::WALK;
walk.startFrame = 5;
walk.endFrame = 8;
gameSystem::AppCtx::AssetMgr().Fetch<asset::Animation>()
    ->CreateAnimCategory("Player", { idle, walk });
auto anim = m_compMgr->AddComponent<component::Animator>(this);
anim->AddAnim(AssetName::IDLE);
anim->AddAnim(AssetName::WALK);
```

`AssetName`はPlayer内の既存定義です。別クラスへ移すなら独自の名前を定義し、同名アセットの衝突を避けます。

## 再生を切り替える

```cpp
// Player::Update()内の考え方
auto anim = m_compMgr->GetComponent<component::Animator>();
if (m_velocity.x != 0) {
    anim->SwitchAnim(AssetName::WALK, AssetName::IDLE);
} else {
    anim->SwitchAnim(AssetName::IDLE, AssetName::WALK);
}
```

第1引数が再生する名前、第2引数が停止・非表示にする名前です。両方を`AddAnim`してから呼びます。`EnableAnim`は名前に反して現行実装では非表示化に使われています。

## 確認する

移動と停止で絵が切り替わることを確認し、`animationSpeed`だけを変えて違いを観察します。フレーム値は画像配列の添字になるため範囲内に収めます。LOOPはendFrame到達時に先頭へ戻ります。ONCEの終了制御やPINGPONGの端点は未検証なので、この実習はLOOPに限定します。

アセットのフレーム配列は借用ポインタで参照されます。描画中に対応画像を削除しないでください。

次：[サウンド](./sound.md) · 参照：[Asset API](../api/asset.md)
