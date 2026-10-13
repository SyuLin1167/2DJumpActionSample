# 基本構造

## フォルダーの役割

| 場所 | 内容 |
| --- | --- |
| ProjectName/code/GameSystem | 起動・終了、カメラ、フレーム時間、共有機能 |
| ProjectName/code/Object | GameObject、管理クラス、Player・Enemy・Map・Goal |
| ProjectName/code/Component | 動作を追加するComponent群 |
| ProjectName/code/Collision | 形状、衝突判定、解決、イベント、管理 |
| ProjectName/code/Asset | 画像・音声・アニメーションの資源管理 |
| ProjectName/code/Scene | 画面の単位と遷移 |
| ProjectName/code/UI | ボタンとUI要素管理 |
| ProjectName/include/MyLib | 入力、数学、ファイル、タスクなどの補助機能 |
| ProjectName/resources | 画像・音声・JSON・CSV |
| ProjectName/project | Visual Studioプロジェクト設定 |
| docs | 文書サイト。C++のビルドとは独立 |

## 最初に読むコード

`main.cpp` → `Execution.cpp` → `SceneManager.cpp` → `Title.cpp` → `LoadingScene.cpp` → `Play.cpp` → `Player.cpp`の順に追うと、開始からゲーム内の処理までつながります。

## 所有関係の概要

```text
Execution
├─ Library
└─ SceneManager
   └─ SceneBase（現在のシーン）
      └─ ObjectManager
         ├─ ColliderManager
         └─ GameObject群
            └─ ComponentManager → Component群

AppContext → FileSystem / AssetManager / UIManager
```

矢印は主な管理関係を示します。すべてが同じスマートポインタ型という意味ではありません。シーンやオブジェクトには共有所有、コライダーやUI要素には単独所有が使われています。[所有権の詳細](../architecture/ownership.md)
