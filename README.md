# 2DGameSample

C++20 ModulesとDxLibで構築した、**2Dゲーム制作のための開発用サンプル**です。オブジェクト、コンポーネント、衝突判定、シーン、アセット管理を学び、自分のゲームへ応用することを目的としています。

付属のジャンプアクションは各機能の利用例です。各ジャンルの完成済みテンプレートを提供するものではありません。

## デモ

付属ゲームでは移動・ジャンプ・地形との衝突・アニメーション・歩行音・ゴール到達によるシーン切り替えを確認できます。

タイトル画面の実機キャプチャです（2026-10-13、既存のRelease実行ファイル。ソースとの一致は未検証）。

![付属ゲームのタイトル画面](docs/public/media/title-2026-10-13.jpg)

プレイ画面と動画は準備中です。[掲載素材の準備項目](docs/project/media.md)を参照してください。

## 主な特徴

- **コンポーネントの組合せ**：移動、ジャンプ、アニメーション、音声操作をGameObjectへ追加。
- **形状別の衝突処理**：矩形・円・タイル、フィルタ、接触イベント、Visitorによる処理の振り分け。円とタイルの組合せは未対応。
- **非同期読み込み**：段階別タスク、進捗・失敗通知、メインスレッドへの結果反映。
- **寿命管理**：シーン単位のコライダー管理、コライダー・UIの世代付きID。
- **ゲームを構成する機能**：シーン遷移、追従カメラ、JSON／CSVのマップ、画像・アニメーション・サウンド管理。

機能の存在と動作保証は区別しています。[実装状況・既知の制約](docs/project/status.md)も確認してください。

## 使用技術

| 項目 | 内容 |
| --- | --- |
| 言語 | C++20、Modules、コルーチン |
| 開発環境 | Visual Studio 2026、Windows向け |
| 推奨ビルド構成 | Debug / Release・x64、MSVC v143 |
| ゲームライブラリ | DxLib（setup.batの指定は3.24f） |
| データ | nlohmann/json、CSV、Windowsメモリマップファイル |

本ガイドは**x64・v143**を対象とします。nlohmann/jsonは現行セットアップでdevelopブランチから取得され、版が固定されていません。

## アーキテクチャ

```text
Execution / AppContext
└─ SceneManager → SceneBase
   └─ ObjectManager
      ├─ GameObject → ComponentManager → 移動・ジャンプ・描画・音声
      └─ ColliderManager → Collider → Visitor / Resolver

共有機能：AssetManager / FileSystem / UIManager
読み込み：LoadingScene → Loading → メインスレッドへ結果反映
```

[基本構造](docs/guide/structure.md)・[更新順序](docs/guide/lifecycle.md)・[設計解説](docs/architecture/index.md)

## セットアップ・ビルド

1. Visual Studio 2026に「C++によるデスクトップ開発」、MSVC v143のx64/x86ビルドツール、Windows SDKを用意します。
2. リポジトリを取得します。

   ```powershell
   git clone --branch develop-dxlib https://github.com/SyuLin1167/2DGameSample.git
   cd 2DGameSample
   .\setup.bat
   ```

3. `ProjectName/2DGameSample.sln`を開きます。
4. `Debug | x64`でビルド・実行します。

`setup.bat`はDxLibとnlohmann/jsonを取得します。必ずリポジトリ直下から実行してください。初回起動にプロジェクト名変更は不要です。起動時は元のresourcesを出力先へコピーするため、ソース側の配置を維持してください。

詳細：[環境構築](docs/guide/environment.md)・[導入と実行](docs/guide/quickstart.md)・[トラブルシューティング](docs/guide/troubleshooting.md)

## 操作方法

| 画面 | 操作 |
| --- | --- |
| タイトル | Startを左クリックして開始、Exitを左クリックして終了 |
| プレイ | ← / →で移動、Spaceでジャンプ |
| ゴール | GOALとの接触でリザルトへ |
| リザルト | Rでタイトルへ |

## ドキュメント

公開サイトは未公開です。リポジトリ内の文書から閲覧できます。

- [利用ガイド](docs/guide/index.md)：環境構築からゲーム制作まで
- [チュートリアル](docs/tutorials/index.md)：機能を順に学ぶ8つの実習
- [APIリファレンス](docs/api/index.md)：公開インターフェース、使用例、制約
- [サイトのローカル閲覧](docs/project/documentation.md)：Node.jsが必要なのは文書サイトの開発時だけです

## 開発目的・今後

ゲーム開発の設計・実装を学び、その仕組みを学生が読み解いてゲーム制作に活用できる教材にすることを目指しています。学校への提供・導入実績は、このリポジトリでは確認していません。

今後の整備候補は、導入手順と教材例の実機検証、既知の制約の改善、依存ライブラリの版固定、素材クレジットの整理です。SDL、ImGui、FMODは現行ブランチの実装済み機能として扱いません。

## ライセンス・利用上の注意

本リポジトリには[MIT License](LICENSE)が適用されています。外部ライブラリや画像・音声の条件は別途確認が必要です。素材の出典・再配布条件は整理中のため、すべての素材をMITとみなさないでください。[ライセンス・素材確認](docs/project/credits.md)

コード確認基準：`develop-dxlib` / `08f9fa53fa5e9043d46aeede8e7aab7bab519892`（2026-10-12）。C++のビルド・ゲーム動作・教材コードのコンパイルは今回の文書整備では未検証です。
