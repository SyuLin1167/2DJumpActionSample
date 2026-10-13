# MyLib

## 入力

`input::KeyStatus::UpdateKeyState()`はvoid、`CheckKey(const int key, const int state)`はboolです。keyは`keyType.LEFT`など、stateはON_PRESS／PRESSING／ON_RELEASE／RELEASINGのビット指定です。SceneManagerが毎フレーム更新します。

MouseStatusはマウス位置、クリック状態の更新・照会、ClickStatusはクリック状態を扱います。正確な公開宣言は[モジュール索引](./modules.md)から確認できます。

```cpp
if (input::KeyStatus::CheckKey(keyType.SPACE, ON_PRESS)) {
    // 押した瞬間の処理
}
```

## Loading

モジュール：`MyLib.Loading`、名前空間：`task`。

| 関数 | 引数・戻り値・制約 |
| --- | --- |
| `void StartLoading()` | 状態初期化。実行中に呼ばない |
| `void AddTask(Level level, std::function<void()> task)` | メインスレッドで登録。無効なlevelや空関数は無視 |
| `void Run()` | 全登録後に実行開始。1インスタンス1回の利用を前提にする |
| `void ReportFailure(const std::string& reason)` | 失敗を通知 |
| `void PostToMain(std::function<void()> commit)` | メイン実行キューへ予約。ワーカーから呼べる |
| `void PumpMain()` | 予約済み処理をメインスレッドで実行 |
| `bool IsLoading() const` | ワーカー処理中か |
| `bool HasFailed() const` | 失敗フラグ |
| `std::string FailureReason() const` | 記録された失敗理由のコピー |
| `float NowProgress() const` | 終了タスク数／総数。総数0なら1。失敗・スキップも終了に含む |

LevelはDATA→INIT→GRAPH→SOUND→FINAL。段階間は完了待ち、同一段階はstd::asyncで並列実行します。ENDは境界値でタスクの種類ではありません。デストラクターは未開始タスクを中断するフラグを立て、実行中タスクの終了を待ちます。強制中断やタイムアウトではありません。

LoadingScene内で有効なコンテキストから使う例：

```cpp
auto* loading = task::LoadingContext::Get();
loading->AddTask(task::INIT, [loading]() {
    // 重い計算を一時データ上で行う
    loading->PostToMain([]() {
        // 結果を共有状態へ反映する
    });
});
// RunとPumpMainはLoadingSceneが担当する
```

## LoadingContext / Coroutine

LoadingContextのstatic関数は`Set(Loading*)`、`Get()`、`Release()`です。GetはLoading*、ほかはvoid。ポインタはthread_localで、ワーカーへ自動継承されません。Releaseはdeleteを行うため、スタック上のLoadingをSetしてReleaseすることはできません。

Coroutineはムーブ専用でハンドルを破棄時に解放します。`resume() const`は継続可能かboolを返し、`get_yield_type() const`はYieldTypeを返します。空ハンドルで後者を呼ばないでください。WaitForSecondsはseconds、WaitUntilはbool関数predを保持します。待ち時間や条件の評価はLoadingScene側が行います。

## FileSystem

`GetExeDir()`／`GetResourcesDir()`／`GetDataDir()`／`GetAssetsDir()`／`GetShaderDir()`はfilesystem::pathを返します。`Mount(const std::string& scheme, const fs::path& root)`はvoid、`Resolve(std::string_view path) const`はfs::path、`CopyDir(fs::path from, fs::path to)`はvoidです。初期化時にexe／resources／data／assets／shaderを登録します。

```cpp
auto path = gameSystem::AppCtx::FileSystem().Resolve("data://PlayerData.json");
auto data = gameSystem::AppCtx::FileSystem().jsonIO.Load(path);
```

CopyDirは再帰コピーと上書きを行い、失敗時に例外を送出します。仮想パス解決はサンドボックス機能ではありません。

## JsonIO / CsvIO / MemMapFile

| クラス・関数 | 引数・戻り値・注意 |
| --- | --- |
| `JsonIO::Load(path)` | jsonを返す。開けない場合・JSON構文エラーは例外 |
| `JsonIO::Load(path, json& data)` | void。参照先へ格納 |
| `JsonIO::LoadAsync(path)` | future&lt;json&gt;。コンテキスト外はその場で実行。future.getで例外を確認 |
| `JsonIO::Write(path, json data)` | void。明示的な.json拡張子を推奨。拡張子補完は一時文字列を書き換える要確認実装 |
| `CsvIO::Load(path)` | MemMapFileをムーブで返す |
| `CsvIO::LoadAsync(path)` | future&lt;MemMapFile&gt; |
| `CsvIO::Parse(const MemMapFile&)` | vector&lt;string_view&gt;。元マップの寿命に依存 |
| `CsvIO::CreateArray<T>(path)` / `(const vector<string_view>&)` | vector&lt;T&gt;。変換失敗は例外 |
| `CsvIO::CreateArrayAsync<T>(path)` | future&lt;vector&lt;T&gt;&gt; |
| `CsvIO::CreateArrayAsync<T>(path, vector<T>& result)` | void。完了までresultの寿命・同期を呼び出し側で保証 |
| `MemMapFile::Open(const char* fileName)` | bool。成功を確認してからGetPtrを使う |
| `MemMapFile::GetPtr()` | char*／const char*の借用ポインタ |
| `MemMapFile::GetFileSize() const` | size_t。ファイルサイズ |
| `MemMapFile::Close()` | void。ポインタとそこから作ったviewが無効になる |

CSVはカンマ・改行で分割する単純な数値用実装です。空セルの保持や引用符付きCSVを前提にしません。数値変換の末尾までの検証も完全ではありません。配列長とマップ寸法の整合はデータ作成時に確認してください。

## 数学・形状・タイル補助

Vector2は2成分の演算、PropVector2は既存Vector2への参照アクセサーです。PropVector2のAdd／Assignで軸またはベクトルを更新し、NowPosは参照、NowX／NowYは値を返します。RectとCircleは形状の補助、TileChunkUtilはマップデータのチャンク化を担当します。

各演算子・テンプレート・形状関数の正確な宣言と説明コメントは[全モジュール](./modules.md)に掲載しています。タスクやファイルの制約は[実装状況](../project/status.md)も参照してください。
