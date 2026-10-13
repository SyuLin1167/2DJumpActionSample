# 07 シーンを切り替える

## 自作シーンを作る

ここからは画像やマップの読み込みを使わない独立した実習です。`ProjectName/code/Scene/Lesson.ixx`を作り、プロジェクトへ登録します。

```cpp
module;
#include <DxLib.h>
export module Scene.Lesson;
import Scene.SceneBase;
import MyLib.KeyStatus;

export namespace scene {
class Lesson final : public SceneBase {
public:
    void Init() override {}
    SceneCmd Update() override {
        if (input::KeyStatus::CheckKey(keyType.R, ON_PRESS)) return CmdPop{};
        return std::monostate{};
    }
    void Draw() override {
        DrawString(100, 100, "Lesson: press R to return", GetColor(255, 255, 255));
    }
};
}
```

## タイトルから積む

Title.cppへ`import Scene.Lesson;`を追加します。`Title::Update()`の冒頭へ次を追加すると、Spaceからこのシーンへ入れます。既存のStartボタンの処理は残します。

```cpp
if (input::KeyStatus::CheckKey(keyType.SPACE, ON_PRESS)) {
    return scene::CmdPush{ []() { return std::make_shared<scene::Lesson>(); } };
}
```

`CmdPush`は下のTitleを保持し、Lessonを上に積みます。Rの`CmdPop`でTitleへ戻れます。これは必ずPushで入る前提です。唯一のシーンをPopすると次のフレームに空のスタックへアクセスするため、終了には`CmdQuit`を使ってください。

## 確認する

タイトルでSpace → Lesson表示 → Rで元のタイトル、を確認します。シーンはフレーム終端で切り替わり、構築後に`Init()`が呼ばれます。下のシーンが自動で更新・描画されるわけではありません。

画像やMapを作るシーンでは読み込みの完了を待つ必要があります。既存Title→LoadingScene→Playの経路を参考にし、特にMapをLoadingContextなしで生成しないでください。

次：[小さなゲーム](./mini-game.md) · 参照：[Scene API](../api/scene.md)
