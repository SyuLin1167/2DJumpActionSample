# Asset

名前空間は`asset`です。アセット管理はDxLibの画像・音声ハンドルの寿命を扱います。再生状態は[Component](./component.md)側です。

## AssetManager / AssetBase

`AssetManager::Fetch<T>()`は`T*`を返し、型未登録なら生成します。所有権は管理側にあります。`Load<T>(std::string name, std::string path)`／`LoadAsync<T>(...)`／`DeleteHandle<T>(std::string name)`はvoidです。削除は型が未登録だと`at()`の例外になり得るため、登録済みの型・名前を使います。

AssetBaseは`CreateHandle(name, fileName)`、`CreateHandleAsync(name, fileName)`、`DeleteHandle(name)`を抽象インターフェースとして持ちます。引数はstd::string、戻り値はvoidです。各派生で画像・音声のパス解決が異なります。

## Graph / DivisionGraph

Graphは1枚の画像を扱い、`GetHandle(std::string name) const`はint、未登録なら-1を返します。DivisionGraphは分割画像を扱います。

| DivisionGraphの関数 | 引数・戻り値・注意 |
| --- | --- |
| `ChangeDivSize(width, height)` | 分割寸法を変更。正の寸法を使う |
| `CreateHandle` / `CreateHandleAsync` | 名前と画像名を受ける。void |
| `GetHandle(std::string name) const` | 配列の借用int*。未登録はnullptr |
| `GetHandle(std::string name, size_t index) const` | 画像ハンドル。未登録・範囲外は-1 |
| `int GetTotalDiv(std::string name) const` | 分割数。未登録名はat()による例外 |
| `DeleteHandle(std::string name)` | 対応画像を解放。既存の借用配列を使い続けない |

Async版はLoadingContext内でタスク登録します。外では呼び出し元で完了を待つ経路です。「必ずすぐ戻る関数」として使わないでください。

## Animation / AnimationDef

画像ハンドル生成は2引数版と、`const int& sizeX, const int& sizeY`を追加した分割寸法指定版があります。同期／非同期の両方があります。

| 関数 | 役割 |
| --- | --- |
| `void CreateAnim(const AnimationDef& animDef)` | 定義名に対応する画像から1定義を作る |
| `void CreateAnimCategory(const std::string& category, const std::vector<AnimationDef> animDefs)` | 同じ分割画像を使う複数定義を作る |
| `GetAnim(const std::string& animName) const` | `const std::pair<int*, AnimationDef>`を値で返す。配列は借用。未登録は空の値 |
| `void DeleteAnim(const std::string& animName)` | 同名の画像削除も試み、定義を消す |
| `void DeleteHandle(std::string name)` | 元の分割画像を削除 |

AnimationDefはname、type、startFrame、endFrame、animationSpeed、sizeです。列挙AnimTypeにはLOOP／ONCE／PINGPONGがありますが、列挙の存在は再生実装の完成を意味しません。教材はLOOPを使用します。

## Sound / SoundDef

`AddSound(const SoundDef& soundDef, std::string fileName = "")`はvoidです。空のファイル名なら定義のみ、指定ありなら定義登録と非同期読み込みを行います。SEのフォルダーを確認し、BGM側へ進む読み込み経路があります。

`GetSound(const std::string& soundName) const`はSoundInfoの値を返します。名前がなければhandleは-1です。戻り型はクラス内の型なので、呼び出し側は`auto`で受け取れます。`DeleteHandle(name)`はDxLibハンドルを削除しますが登録を消さず、`DeleteSound(name)`は登録も消します。

SoundDefはsoundType、playType、name、volumeです。playTypeは現在のAudioSourceでは参照されません。定義は`SoundDef def{};`で初期化し、使用するフィールドを明示します。

## 使用例

```cpp
// AppContextの有効期間内。素材を使う場合はその利用条件も確認する
gameSystem::AppCtx::AssetMgr().Load<asset::Graph>("lesson-bg", "bg.png");
auto* graph = gameSystem::AppCtx::AssetMgr().Fetch<asset::Graph>();
int handle = graph->GetHandle("lesson-bg");
// handle != -1を確認して描画する
gameSystem::AppCtx::AssetMgr().DeleteHandle<asset::Graph>("lesson-bg");
```

同名アセットを複数オブジェクトで使用する場合、削除がほかの利用者へ影響します。参照カウントによる個別のアセット貸出管理ではありません。

[アニメーション実習](../tutorials/animation.md) · [音声実習](../tutorials/sound.md) · [全モジュール](./modules.md)
