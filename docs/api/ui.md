# UI

## UIBase

モジュール：`UI.UIBase`。UIの位置・サイズ・可視状態を持ちます。

| 関数 | 引数・戻り値 |
| --- | --- |
| `SetPosition(const Vector2f& pos)` / `SetSize(const Vector2f& size)` | void。位置／サイズ設定 |
| `SetVisible(bool visible)` | void。可視状態設定 |
| `GetPosition() const` / `GetSize() const` | `const Vector2f&` |
| `IsVisible() const` | bool |
| `Update()` / `Draw()` | virtual void。既定は空 |

## UIManager

`Create<T>(Args&&... args)`はコンストラクター引数を転送し、UIElementIDを返します。管理側が要素をunique_ptrで所有します。

`GetElement(const UIElementID&)`はUIBase*を返し、無効なIDならnullptr。`Destroy(id)`はvoidで、無効IDを無視します。`Clear()`は全要素を削除し、既存IDを無効にします。`Update()`と`Draw()`はいずれもvoidです。

IDはindexとgenerationを持ちます。返されたIDを保存し、同じ管理インスタンスで使います。UIElementIDの値初期化だけで無効IDになるとは限らないため、CreateしていないIDをDestroyしないでください。

## Button / ButtonDef

`ButtonDef(const std::string& text, const shape::Rect& buttonRect, uint32_t color)`は表示文字・矩形・色を設定します。onHover、onClicked、onReleasedはいずれも`std::function<void()>`です。

`Button(const ButtonDef* def)`は定義をコピーします。非nullの定義を渡してください。`SetText(const std::string&)`、`SetOnMouseHover(std::function<void()>)`、`SetOnClicked(...)`、`SetOnReleased(...)`はvoidで設定を置換します。UpdateとDrawをoverrideしています。

## 使用例

```cpp
// AppContext有効期間内。idはシーンのメンバー等へ保存する
shape::Rect rect({100.0f, 100.0f}, {160.0f, 48.0f});
ui::ButtonDef def("Start", rect, GetColor(80, 120, 100));
def.onReleased = [this]() { m_toNextScene = true; };
auto id = gameSystem::AppCtx::UIMgr().Create<ui::Button>(&def);
```

Titleがこの形で利用しています。シーン更新・描画からUIMgrのUpdate／Drawを呼び、シーン破棄時にDestroy(id)します。コールバックが捕捉するthisよりボタンが長生きしないようにしてください。コールバック中に管理コンテナーを直接消すより、フラグで遷移要求を伝えます。

不可視のButtonは更新も描画も行いません。解放イベントはボタン内の入力判定に依存します。[所有権](../architecture/ownership.md) · [全モジュール](./modules.md)
