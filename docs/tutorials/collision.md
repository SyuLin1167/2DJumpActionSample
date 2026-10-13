# 04 衝突判定と接触イベント

この章では既存Playerの処理を読み解きます。01〜03のLessonBoxへそのまま追加する例ではありません。Playerに同じコライダーを二重登録しないでください。

## 生成する

`Player::Init()`では概ね次の設定を行っています。`pData`と`id`はPlayerの既存メンバーです。

```cpp
col2d::ColliderDef def{};
def.localPos = m_pos;
def.isActive = true;
def.shouldCCD = true;
id = ColMgr().CreateRectCollider(&def, pData.size, MyObjectTag());
ColMgr().AddMask(id, col2d::CIRCLE, object::ObjectTag::ENEMY);
```

`def`は生成時にコピーされます。`ColMgr()`は所属するシーンの管理機能です。GameObjectのコンストラクター時点ではまだ設定されていないため、`Init()`や`OnAttach()`以降に使用します。

## 接触イベントを読む

Playerは上向きの法線を持つ地形との接触を着地として扱います。次はPlayer内の登録例で、`jump`は追加済みJumpコンポーネントです。

```cpp
col2d::ContactListener listener;
listener.when = [](const col2d::ContactInfo& info) {
    return info.normal == col2d::NORMAL_TOP;
};
listener.event = [jump]() { jump->CanJump(); };
ColMgr().AddEvent(id, col2d::MakeKey(col2d::TILE, object::ObjectTag::MAP), listener);
```

マスクは衝突処理を呼ぶ相手、イベントキーは通知を受ける相手のカテゴリです。地形側がPlayerに対するマスクを持つことで、TileColliderVisitorから矩形への処理が呼ばれます。

## 移動と破棄

Playerの`Update()`で`SetVelocity(m_velocity)`、`LateUpdate()`で解決後の座標と移動量を受け取ります。取得したポインタが有効か確認し、デストラクターでは`Destroy(id)`を呼びます。

```cpp
if (auto* collider = ColMgr().GetCollider(id)) {
    collider->SetVelocity(m_velocity);
}
```

## 確認する

既存Playerで地面への着地、ジャンプ、Enemyへの接触を観察します。法線条件を外した場合との違いを考えてください。円対タイルは未対応、トリガーの押し戻し条件にも要確認箇所があります。完全な物理シミュレーターとして扱わないでください。

次：[アニメーション](./animation.md) · 参照：[Collision API](../api/collision.md)
