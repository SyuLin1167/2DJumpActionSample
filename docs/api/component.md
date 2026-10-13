# Component

## ComponentBaseとComponentManager

モジュールは`Component`と`Component.ComponentManager`、名前空間は`component`です。

`ComponentBase(GameObject* owner)`は所有しないポインタを保持します。`Update(const float& deltaTime)`と`Draw()`は仮想関数で既定は空です。所有者を使う派生クラスでは、ownerを渡して生成してください。

| ComponentManagerの公開関数 | 引数・戻り値・役割 |
| --- | --- |
| `AddComponent<T>(Args&&... args)` | コンストラクター引数を転送。`shared_ptr<T>`を返す。同型登録を置換 |
| `GetComponent<T>()` | `shared_ptr<T>`。未登録ならnullptr |
| `HasComponent<T>()` | `bool`。型の登録有無 |
| `RemoveComponent<T>()` | `void`。登録を除去。外部のshared_ptrがあれば寿命は延びる |
| `Update(const float& deltaTime)` | `void`。全Componentを更新 |
| `Draw()` | `void`。全Componentを描画 |

追加順の更新は保証しません。Componentの更新中に管理コンテナーを変更する使い方も避けてください。

## MoveWithKey

`MoveWithKey(GameObject* owner)`で生成します。

| 関数 | 説明 |
| --- | --- |
| `void SetHorizontal(int leftKey, int rightKey, float moveSpeed)` | 左右キーと速度を設定 |
| `void SetVertical(int upKey, int downKey, float moveSpeed)` | 上下キーと速度を設定。ただし現行UpdateはY計算にX速度を使用する問題あり |
| `const bool CanMoveHorizontal()` / `CanMoveVertical()` | 設定済みの移動軸が有効か返す |
| `void Update(const float& deltaTime)` | キー状態からフレーム移動量を所有者へ設定 |

水平移動の例（GameObject派生のInit内）：

```cpp
auto move = m_compMgr->AddComponent<component::MoveWithKey>(this);
move->SetHorizontal(keyType.LEFT, keyType.RIGHT, 180.0f);
```

必要なimportと座標への反映は[入力実習](../tutorials/input.md)にあります。

## Jump

`Jump(GameObject* owner, const float& jumpPower = DEFAULT_JUMP_POWER, std::function<bool()> trigger = {})`。triggerは押下判定、jumpPowerは上向きの初速設定です。実装はtriggerを無条件に呼ぶため、空の関数を使わないでください。

`Update(deltaTime)`はジャンプ判定と重力処理、`TryJump(deltaTime)`は許可されていればジャンプ開始、`CanJump()`は着地時の許可と垂直速度リセットを行います。いずれも戻り値はvoidです。重力の加算自体はフレームごとなので、完全にフレームレート非依存とは説明しません。

## Animator

`Animator(GameObject* owner)`で生成します。以下の制御関数の戻り値はvoid、名前の引数は`const std::string&`です。

| 関数 | 動作 |
| --- | --- |
| `AddAnim(animName)` | 登録済みアニメーションから再生状態を追加 |
| `PlayAnim(animName)` | 非表示を解除して再生状態にする |
| `PauseAnim(animName)` | 現在フレームで一時停止。描画は継続 |
| `StopAnim(animName)` | 停止し開始フレームへ戻す。非表示化とは別 |
| `TurnAnimGraph(animName)` | 左右反転フラグを切り替える |
| `EnableAnim(animName)` | 現行実装では非表示化。名前と意味に注意 |
| `SwitchAnim(issueName, targetName)` | targetを停止・非表示化し、issueを再生 |
| `Update(deltaTime)` / `Draw()` | 時間に応じたフレーム更新／所有者座標で描画 |

事前にAsset側で定義を作り、`AddAnim`を呼びます。未登録名を渡すと`at()`による例外が起こり得ます。ONCEの終了処理は未整備、PINGPONG端点と配列範囲は検証対象です。[アニメーション実習](../tutorials/animation.md)

## AudioSource

`AudioSource(GameObject* owner)`で生成します。`Play(const std::string& soundName)`、`Pause(...)`、`Stop(...)`はいずれもvoidです。未取得ハンドルなら処理を行いません。SE_ONCEはハンドルを複製し、ほかの種別はループ再生の経路へ入ります。

単発SEの複製ハンドルは再生終了時に自動解放されますが、その音をPause／Stopで個別制御する仕組みではありません。ループ音は名前に対応する共有ハンドルを操作します。複数AudioSourceで同じ音を独立制御できるとは限りません。

[サウンド実習](../tutorials/sound.md) · [Asset API](./asset.md) · [全モジュール](./modules.md)
