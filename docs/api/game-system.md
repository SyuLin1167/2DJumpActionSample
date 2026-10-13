# GameSystem

## ExecutionとLibrary

`gameSystem::Execution`はAppContextを有効にし、resourcesをコピーし、LibraryとSceneManagerを生成します。`int Run()`はライブラリ初期化失敗時に-1、それ以外はゲームループ後のメモリリーク検査の結果を返します。一般的なゲーム終了コードと同じとは限りません。

`Library`はDxLibの初期化・終了を担当します。`InitSuccess()`で初期化結果を確認します。これらはアプリケーション入口で使用し、各シーンから新しく生成するものではありません。

## AppContext

モジュール：`AppContext`。`gameSystem::AppCtx`は`AppContext`の別名です。

| static関数 | 戻り値・役割 |
| --- | --- |
| `Activate()` | void。共有管理インスタンスを構築 |
| `Deactivate()` | void。共有管理インスタンスを破棄 |
| `FileSystem()` | `file::FileSystem&` |
| `AssetMgr()` | `asset::AssetManager&` |
| `UIMgr()` | `ui::UIManager&` |

すべて引数なしです。参照取得は有効期間内に限ります。Executionが有効化・無効化を行うため、教材の各オブジェクトからActivateを呼ばないでください。

## FrameRate・Window

`FrameRate::CalcFrameRate()`はvoidで時間を更新し、`GetDeltaTime()`は`const float&`で秒単位の差分を返します。`DrawFrameRate()`はDebug時のみ存在します。更新はSceneManagerが担当します。

`Window::Init()`はvoid、`GetWindowData()`は内部Infoへのconstポインタです。InfoのSIZEは1920×1080、COLOR_BITは32です。公開のリサイズ設定APIはありません。

## Camera

| 関数 | 引数・戻り値・意味 |
| --- | --- |
| `static Camera& Instance()` | カメラへの参照 |
| `void SetTarget(Vector2f* target)` | 追従する座標への非所有ポインタ |
| `void ClearTarget(const Vector2f* target)` | 登録中のポインタと同じときだけ解除 |
| `void SetWorldSize(const Vector2f& worldSize = Vector2f(1920.0f, 1080.0f))` | ワールド範囲を設定 |
| `void Update()` | 追従更新。ObjectManagerが呼ぶ |
| `Vector2f GetOffset() const` | 現在のカメラ位置 |
| `Vector2f WorldToScreen(const Vector2f& worldPos) const` | 座標からオフセットを引く |
| `Vector2f WorldToScreen(float x, float y) const` | 2成分指定の座標変換 |

GameObject派生クラスでの使用例：

```cpp
// Init内
gameSystem::Camera::Instance().SetTarget(&m_pos);
// Draw内
auto screen = gameSystem::Camera::Instance().WorldToScreen(m_pos);
// デストラクター内
gameSystem::Camera::Instance().ClearTarget(&m_pos);
```

ローカル変数のアドレスをSetTargetへ渡さないでください。[寿命管理](../architecture/ownership.md) · [全モジュール](./modules.md)
