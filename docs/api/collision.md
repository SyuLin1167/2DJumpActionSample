# Collision

名前空間は`col2d`です。単に重なりを調べる処理、押し戻す処理、接触イベントを区別します。

## ColliderManager

モジュール：`Collider.ColliderManager`。

| 公開関数 | 引数・戻り値 |
| --- | --- |
| `CreateCollider<T>(ColliderDef* def, const uint32_t& ownerID, Args&&... args)` | 定義・所有者カテゴリ・形状固有引数から生成。ColliderIDを返す |
| `CreateRectCollider(def, const Vector2f& size, ownerID = 0)` | 矩形のサイズ。ColliderIDを返す |
| `CreateCircleCollider(def, float radius, ownerID = 0)` | 円の半径。ColliderIDを返す |
| `CreateTileCollider(def, const MapInfo& info, std::string fileName, ownerID = 0)` | マップ定義とCSV名。ColliderIDを返す |
| `CreateTileCollider(def, std::shared_future<MapInfo> info, std::string fileName, ownerID = 0)` | マップ構築結果を待つ版。ColliderIDを返す |
| `Collider* GetCollider(const ColliderID& id) const` | 借用ポインタ。無効・旧世代IDはnullptr |
| `void Destroy(const ColliderID& id)` | コライダー破棄。無効・旧世代IDは無視 |
| `void AddMask(id, const uint32_t& shape, const uint32_t& ownerID)` | 判定対象カテゴリを追加 |
| `void AddEvent(id, const uint64_t& key, ContactListener event)` | カテゴリのイベントを追加 |
| `void Step()` | マスクで対象を選び、衝突と移動を実行 |

defは非nullで渡し、`ColliderDef def{};`のように値初期化します。Collider内部で定義をコピーします。IDは`index`と`generation`を持ち、生成元の管理インスタンスでのみ使います。異なるシーンのIDを混ぜないでください。

## Colliderと定義

`Collider`は`GetColliderDef()`、`GetFilter()`、`SetVelocity(const Vector2f&)`、`GetVelocity()`、`AddVelocity()`、`Accept(ColliderVisitor&)`、`CollideWith(Collider&)`、`GenerateCategory(uint32_t)`、`AddEvent(key, event)`、`TriggerEvent(key, info)`、`DeleteEvent(key)`を公開します。

取得関数は内部の定義ポインタ／Filter参照／移動量の値を返し、操作関数はvoidです。`GetColliderDef()`は可変ポインタですが、形状側の内部情報もあるため、定義の書換えだけで全形状状態が追従するとは限りません。

`ColliderDef`にはtype、worldPos、localPos、shouldCCD、isTrigger、isActiveがあります。`ContactInfo`には法線normalと接触点pointがあります。`ContactListener`は`bool(const ContactInfo&)`のwhenと、`void()`のeventです。

## 形状と解決

RectCollider・CircleColliderは相手形状や点との`IsColliding`、形状取得、移動を実装します。Rectにはswept矩形の計算があり、Visitorはサブステップも使います。これは全速度に対するすり抜け防止保証ではありません。

TileColliderはチャンク化したタイルを持ち、`IsColliding(const shape::Rect&)`がboolを返します。`TakeHitTileKeys()`は検出キーのqueueを取り出して内部queueを空にします。`GetTileInfo(key, index)`は借用constポインタで、範囲外ならnullptr。`GetTileSize()`はconst参照です。

TileColliderVisitorは矩形に対応し、円へのVisitは空です。TileCollider自身のAcceptも空なので、地形側から矩形へ訪問する方向を使います。TileTypeはSOLIDとONE_WAY_TOP。Resolverが押し戻しと接触情報を扱います。

Rect／Circle／Tileの各Resolverは形状ごとのResolveを持ちます。返り値が`optional<ContactInfo>`の版は接触情報なしをnulloptで表します。正確な各オーバーロードは[宣言一覧](./modules.md)で確認してください。

## フィルタ・イベント例

`MakeKey(shape, ownerID)`でカテゴリを作ります。Filterのマスクはカテゴリ単位です。オブジェクト個体の識別子ではないので、同じタグの複数個体を別々に指定する仕組みではありません。

```cpp
// GameObject派生のInit内
col2d::ColliderDef def{};
def.isActive = true;
def.localPos = m_pos;
auto id = ColMgr().CreateRectCollider(&def, {32.0f, 32.0f}, MyObjectTag());
ColMgr().AddMask(id, col2d::CIRCLE, object::ObjectTag::ENEMY);
```

実際にはidをメンバーへ保存し、破棄時にDestroyします。[衝突実習](../tutorials/collision.md)を参照してください。トリガーの条件式とコメントの不一致、カテゴリ単位の削除副作用などは[制約](../project/status.md)にまとめています。
