# 03 キー入力で移動する

## Componentを入れ替える

02の自動移動をやめ、既存の`MoveWithKey`を使います。LessonBoxの`LessonDrift`のimport・追加を除き、次のimportを追加します。

```cpp
import Component.MoveWithKey;
import MyLib.KeyStatus;
```

LessonBoxの`Init()`を置き換え、`Update()`を追加します。

```cpp
void Init() override {
    m_pos = { 300.0f, 300.0f };
    auto move = m_compMgr->AddComponent<component::MoveWithKey>(this);
    move->SetHorizontal(keyType.LEFT, keyType.RIGHT, 180.0f);
}
void Update() override {
    m_pos += m_velocity;
}
```

`MoveWithKey`は速度設定にdeltaTimeを掛け、`AccessVel()`へそのフレームの移動量を入れます。この例ではさらにdeltaTimeを掛けません。コライダーを持たないLessonBoxなので、`Update()`で座標へ反映しています。

Playerのようにコライダーが移動を担う場合、この座標加算を重ねないでください。[更新順序](../guide/lifecycle.md)

## キーの状態を読む

次はUpdate内でSpaceを押した瞬間だけ処理する書き方です。

```cpp
if (input::KeyStatus::CheckKey(keyType.SPACE, ON_PRESS)) {
    // 1回だけ実行したい処理
}
```

押し続ける場合は`ON_PRESS | PRESSING`です。入力更新はSceneManagerが行うので、各オブジェクトから再更新しません。

## 確認する

左・右・左右同時・キーを離す、の4通りを試します。左右同時では移動が相殺されます。この例は水平移動のみです。`SetVertical`には速度参照の問題があるため、縦移動の完成例として扱いません。

次：[衝突処理](./collision.md) · 参照：[入力API](../api/mylib.md)
