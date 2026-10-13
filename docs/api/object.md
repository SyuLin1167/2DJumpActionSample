# Object

## GameObject

モジュール：`Object.GameObject`、名前空間：`object`。ゲーム内オブジェクトの抽象基底です。

| 公開関数 | 引数・戻り値・役割 |
| --- | --- |
| `GameObject()` / `virtual ~GameObject()` | 生成・破棄。ComponentManagerを管理 |
| `void Init()` | 引数なし。派生側で必須実装 |
| `void Update()` / `void LateUpdate()` | 通常更新／衝突処理後の更新。既定は空 |
| `void Draw()` | 描画。派生側で必須実装 |
| `void UpdateComponents()` / `void DrawComponents()` | 登録Componentを更新／描画 |
| `uint32_t NowState() const` | 状態のビット値を返す |
| `PropVector2<float> AccessPos()` / `AccessVel()` | 座標／移動量への参照を包んだアクセサーを返す |
| `ObjectTag MyObjectTag() const` | タグを返す。派生側で必須実装 |
| `void SetColliderManager(ColliderManager* mgr)` | 非所有の所属管理ポインタを設定。通常ObjectManagerが呼ぶ |
| `void OnAttach()` | 所属直後の処理。既定は空 |
| `void GetReferenceObject(std::function<std::vector<std::shared_ptr<GameObject>>(uint32_t)> referenceObj)` | タグ検索関数を受け取るフック。既定は空 |

派生側はprotectedの`m_pos`、`m_velocity`、`m_state`、`m_compMgr`、`ColMgr()`を利用できます。`ColMgr()`は未所属なら有効ではありません。`AccessPos()`の戻り値も元オブジェクトより長く保持しないでください。

## ObjectManager

モジュール：`Object.ObjectManager`。シーン内のオブジェクトとコライダーを管理します。

| 公開関数 | 引数・戻り値・役割 |
| --- | --- |
| `AddObject(GameObject* object, Args&&... args)` | `void`。管理するオブジェクトを受け取る。通常はnewしたポインタを渡す |
| `RemoveObject(GameObject* object)` | `void`。一致する登録を除去。外部共有所有があれば即破棄とは限らない |
| `InitBeforeUpdate()` | `void`。参照取得と各Initを実行 |
| `Update()` | `void`。Component→Object→衝突→LateUpdate→カメラ→追加削除 |
| `RefreshObjects()` | `void`。DEAD状態を除去し、追加予約を反映 |
| `GetObjForTag(uint32_t tag)` | `vector<shared_ptr<GameObject>>`。該当群のコピー、未登録なら空 |
| `Draw()` | `void`。ComponentとObjectを描画 |

`AddObject`は所有権を引き受けます。更新中は生ポインタの一時配列へ保存するため、追加の独自deleter等を前提にする使い方は避けます。`RemoveObject`は即時の配列変更なので更新中の削除には使わず、派生クラスで`m_state = MainState::DEAD`とし更新後の除去を利用します。

## タグ・状態・サンプル

`ObjectTag`はNONE／MAP／PLAYER／ENEMY／GOALです。更新対象は`OBJECT_TAGS`を巡回します。新規タグは列挙値だけ増やしても更新対象に入りません。

Playerは入力・ジャンプ・矩形衝突・アニメーション・歩行音の例、Enemyは接触で体力を減らす静的な円、MapはJSON／CSVとタイルの例、Goalは接触でクリアフラグを立てる例です。Mapのコンストラクターは有効なLoadingContextを必要とします。

## 使用例

SceneBaseの派生クラスのコンストラクター内で、登録済みの教材用モジュールを使います。

```cpp
m_objManager->AddObject(new object::LessonBox);
```

続く`Init()`で`m_objManager->InitBeforeUpdate()`を呼びます。完全なクラス例は[01 GameObject](../tutorials/game-object.md)、寿命の制約は[所有権](../architecture/ownership.md)、宣言は[全モジュール](./modules.md)を参照してください。
