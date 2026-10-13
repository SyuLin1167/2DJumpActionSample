# Scene

## SceneBase

モジュール：`Scene.SceneBase`、名前空間：`scene`。`void Init()`、`SceneCmd Update()`、`void Draw()`は派生側で必須実装です。`void DrawLoading()`は任意の読み込み表示で、既定は空です。

protectedの`m_objManager`は`unique_ptr<ObjectManager>`です。`shared_from_this()`を使うシーンはshared_ptrで所有されている必要があります。

## SceneCmd

`SceneBuilder`は`std::function<std::shared_ptr<SceneBase>()>`です。SceneCmdは次の値を含むvariantです。

| 値 | 動作 |
| --- | --- |
| `std::monostate{}` | 現状を継続 |
| `CmdPush{build}` | buildのシーンを積む |
| `CmdReplace{build}` | 現在のシーンを置換 |
| `CmdPop{}` | 最上位のシーンを除く |
| `CmdQuit{}` | アプリケーション終了を要求 |

生成関数がnullを返すとPush／Replaceは適用されません。SceneManagerは更新・描画後にコマンドを適用し、新規シーンのInitを呼びます。初期Titleの生成経路ではInitを呼びませんが、現行TitleのInitは空です。

唯一のシーンをPopする使い方は未対応です。また、下に積まれたシーンは自動更新・自動描画されません。

## SceneManager

`SceneManager()`でTitleを生成します。公開の`void GameLoop()`がメッセージ処理と更新・描画・遷移を繰り返します。Update／Draw／ChangeSceneはprivateです。通常はExecutionからGameLoopを呼びます。

## LoadingScene

```cpp
LoadingScene(int8_t policy,
             std::function<std::shared_ptr<SceneBase>()> nextScene,
             std::shared_ptr<SceneBase> holdScene = nullptr);
```

policyはPROGRESS／COROUTINE／DONE、nextSceneは次のシーンを構築する関数、holdSceneは読み込み中に表示を保持するシーンです。PROGRESSは保持シーンのDrawとDrawLoading、ほかは必要に応じDrawLoadingを呼びます。NONEや既定コンストラクターを実習の通常経路に使わないでください。

`LoadCoroutine()`はCoroutineを返し、`Update()`は進捗・メインキュー・遷移を処理してSceneCmdを返します。`OnLoadFailed()`もSceneCmdを返し、保持シーンがなければ終了、それ以外はTitleへ戻る経路です。Initは空、Drawはvoidです。

使用例はTitle内の次の構造です。

```cpp
return CmdReplace{
    [hold = shared_from_this()]() mutable {
        return std::make_shared<LoadingScene>(LoadPolicy::PROGRESS,
            []() { return std::make_shared<Play>(); }, std::move(hold));
    }
};
```

必要なimportは既存Title.cppを参照してください。ローディングを重ねる・1つのLoadingContextを独自に使い回す設計は前提にしていません。

Title、Play、Resultはこの基底の利用例です。[シーン実習](../tutorials/scene.md) · [非同期設計](../architecture/loading.md) · [全モジュール](./modules.md)
