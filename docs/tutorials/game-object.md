# 01 GameObjectを作って表示する

## 目的と前提

ゲーム内の要素は`GameObject`を継承して作ります。純粋仮想関数の`Init`、`Draw`、`MyObjectTag`を実装します。[基本構造](../guide/structure.md)を先に確認してください。

## クラスを追加する

教材用に`ProjectName/code/Object/LessonBox.ixx`を作り、プロジェクトへ追加します。

```cpp
module;
#include <DxLib.h>

export module Object.LessonBox;
import Object.GameObject;
import GameSystem.Camera;

export namespace object {
class LessonBox final : public GameObject {
public:
    void Init() override { m_pos = { 300.0f, 300.0f }; }
    void Draw() override {
        const auto p = gameSystem::Camera::Instance().WorldToScreen(m_pos);
        DrawBox(static_cast<int>(p.x), static_cast<int>(p.y),
                static_cast<int>(p.x + 32), static_cast<int>(p.y + 32),
                GetColor(80, 190, 160), TRUE);
    }
    ObjectTag MyObjectTag() const override { return ObjectTag::NONE; }
};
}
```

既存の`NONE`タグを使うので、タグ列挙や`OBJECT_TAGS`を変更する必要はありません。新しいタグを将来追加する場合は更新対象の配列も確認してください。

## Playへ登録する

`Play.cpp`のimport群に`import Object.LessonBox;`を追加し、`Play::Play()`内へ次を追加します。

```cpp
m_objManager->AddObject(new object::LessonBox);
```

`AddObject`の戻り値はありません。渡したオブジェクトは管理側が所有します。スタック変数のアドレスや、すでに別の`shared_ptr`で所有しているポインタを渡さないでください。

## 確認する

Startからプレイへ進み、ワールド座標(300, 300)付近に四角があることを確認します。カメラはPlayerを追うため、表示範囲に入るよう座標を調整しても構いません。シーンの`InitBeforeUpdate()`がLessonBoxの`Init()`も呼びます。

表示されないときは、モジュール登録、`AddObject`、カメラ位置を確認します。

次：[Componentを追加する](./component.md) · 参照：[Object API](../api/object.md)
