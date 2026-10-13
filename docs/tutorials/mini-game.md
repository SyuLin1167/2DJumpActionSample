# 08 小さなゲームを作る

## 目標

07のLessonを、左右移動でゴールへ到達する「10秒チャレンジ」に置き換えます。外部素材を使わず、入力・時間・描画・シーンをまとめて使います。衝突管理やアセット読み込みはこの最小例には含めません。

## Lesson.ixxを置き換える

```cpp
module;
#include <DxLib.h>
export module Scene.Lesson;
import Scene.SceneBase;
import MyLib.KeyStatus;
import GameSystem.FrameRate;

export namespace scene {
class Lesson final : public SceneBase {
public:
    void Init() override { x = 120.0f; remaining = 10.0f; state = State::Playing; }
    SceneCmd Update() override {
        if (input::KeyStatus::CheckKey(keyType.R, ON_PRESS)) return CmdPop{};
        if (state != State::Playing) return std::monostate{};
        const float dt = gameSystem::FrameRate::GetDeltaTime();
        remaining -= dt;
        const int right = input::KeyStatus::CheckKey(keyType.RIGHT, ON_PRESS | PRESSING) ? 1 : 0;
        const int left = input::KeyStatus::CheckKey(keyType.LEFT, ON_PRESS | PRESSING) ? 1 : 0;
        x += (right - left) * 120.0f * dt;
        if (x < 0) x = 0;
        if (x >= 900.0f) state = State::Clear;
        else if (remaining <= 0) state = State::Timeout;
        return std::monostate{};
    }
    void Draw() override {
        DrawBox(900, 400, 960, 460, GetColor(240, 200, 70), TRUE);
        DrawBox(static_cast<int>(x), 416, static_cast<int>(x + 28), 444,
                GetColor(80, 190, 160), TRUE);
        DrawFormatString(100, 100, GetColor(255, 255, 255),
                         "Time: %.1f / Left, Right / R: Title", remaining > 0 ? remaining : 0);
        if (state == State::Clear)
            DrawString(100, 150, "CLEAR!", GetColor(80, 220, 160));
        else if (state == State::Timeout)
            DrawString(100, 150, "TIME UP", GetColor(250, 160, 100));
    }
private:
    enum class State { Playing, Clear, Timeout };
    float x = 120.0f;
    float remaining = 10.0f;
    State state = State::Playing;
};
}
```

07のTitle側の`CmdPush`をそのまま使います。Rで戻って入り直せば`Init()`でリセットされます。

## 確認項目

1. 右へ進んでCLEARになる。
2. 操作せず待つとTIME UPになる。
3. 終了状態で移動・時間更新が止まる。
4. Rでタイトルへ戻り、再開すると初期状態になる。
5. 左右同時押しで移動量が0になる。

## 発展課題

01〜03のGameObjectとComponentへ移動処理を分け、シーンはルールだけを担当する形にします。04の知識で座標比較を接触イベントへ置き換え、05〜06の画像・音声を導入する場合はLoadingSceneと資源の後始末も追加します。一度にすべて変更せず、上の確認項目を維持しながら進めてください。

関連：[設計解説](../architecture/index.md)、[既知の制約](../project/status.md)
