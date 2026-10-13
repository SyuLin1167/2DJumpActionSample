# 02 Componentを追加する

## 動作を分ける

01のLessonBoxへ、水平に進む教材用Componentを追加します。`ProjectName/code/Component/LessonDrift.ixx`を作り、プロジェクトへ登録します。

```cpp
export module Component.LessonDrift;
import Component;
import Object.GameObject;

export namespace component {
class LessonDrift final : public ComponentBase {
public:
    explicit LessonDrift(object::GameObject* owner) : ComponentBase(owner) {}
    void Update(const float& deltaTime) override {
        auto position = m_owner->AccessPos();
        auto next = position.NowPos();
        next.x += 60.0f * deltaTime;
        position.Assign(math::PropVector2<float>::X, next.x);
    }
};
}
```

`ComponentBase`の所有者ポインタは参照用です。ComponentがGameObjectを削除することはありません。

## LessonBoxへ追加する

`LessonBox.ixx`に`import Component.LessonDrift;`を追加し、`Init()`を置き換えます。

```cpp
void Init() override {
    m_pos = { 300.0f, 300.0f };
    m_compMgr->AddComponent<component::LessonDrift>(this);
}
```

`m_compMgr`はGameObjectの派生クラスから使えるprotectedメンバーです。`GameObject::AddComponent`という関数は存在しません。

## 確認する

四角が右へ進むことを確認します。`ObjectManager`がComponent更新を呼ぶため、LessonBoxから`UpdateComponents()`を重ねて呼ぶ必要はありません。

同じ型のComponentは1つの登録枠を使います。再追加すると置換されます。また、Component同士の更新順は追加順とは限りません。

次：[入力と移動](./input.md) · 参照：[Component API](../api/component.md)
