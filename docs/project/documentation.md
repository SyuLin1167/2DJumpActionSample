# 文書サイトの開発・公開

## ローカルで閲覧する

Node.js 22以上（検証環境は24系）を用意し、リポジトリ直下から実行します。ゲームのビルドにNode.jsは不要です。

```powershell
cd docs
npm ci
npm run dev
```

表示されたローカルURLを開きます。終了はターミナルでCtrl+Cです。公開用の出力を確認する場合は次を使います。

```powershell
npm run check
npm run build
npm run preview
```

VitePressは1.6.4、依存関係はpackage-lock.jsonで固定しています。生成物は`.vitepress/dist`です。キャッシュ・node_modules・生成物はGitへ追加しません。

## 文書の更新

APIのソース基準は`api/source-manifest.json`に記録します。`npm run check`はローカルリンク、旧名・ユーザー固有パス、モジュール追加・削除・内容変更と転記のずれを確認します。API変更時にCIが止まるのは、説明の再確認が必要という意味です。

基準を更新するときは、各API解説と実習を先に確認し、`scripts/generate-api.mjs`のrevisionを新しい確定コミットへ変更してから`node scripts/generate-api.mjs`を実行します。README・ホーム・検証記録・フッターの基準表示も更新してください。生成だけで説明内容の正しさが保証されるわけではありません。

## GitHub Actions

`docs-check.yml`はPR／develop-dxlibの変更で文書確認とビルドのみを行います。C++ビルドは実行しません。公開は`docs-deploy.yml`に分離し、**リポジトリ変数DOCS_PUBLISH_APPROVEDが文字列trueの場合だけ**実行します。未設定の初期状態では公開ジョブへ進みません。

## 承認後の公開手順

以下は公開準備の手順です。この文書を追加しただけでは実行されません。

1. 変更内容、素材・ライセンス、既知の制約、検証記録を所有者が確認する。
2. 外部公開とPRマージの承認を得て、公開する変更をdevelop-dxlibへ反映する。
3. 所有者の承認後、GitHubのPagesでSourceをGitHub Actionsへ設定する。
4. 必要ならgithub-pages環境に承認者を設定し、DOCS_PUBLISH_APPROVEDをtrueへ設定する。
5. develop-dxlibを選んで公開ワークフローを手動実行し、成功後にURLを確認する。
6. READMEの未公開表記を実際の公開URLへ更新する。

以後はdocs変更のpushで自動公開できます。停止する場合は変数をfalseにします。これは今後のデプロイを止めるだけで、既存の公開サイトを取り下げる操作ではありません。

想定ベースパスは`/2DGameSample/`です。カスタムドメインを使う場合は変更が必要です。[VitePress公式の公開手順](https://vitepress.dev/guide/deploy)

## 公開前の確認

- 画像・音声の作者・出典・利用条件を確定し、未確認素材を掲載しない。
- docs/publicには公開対象だけを置く。resourcesや実行ログを一括コピーしない。
- 追跡済みのProjectName/project/Log.txtには環境情報があるため、リポジトリ側での扱いも所有者が判断する。
- スクリーンショットや動画に通知、個人情報、ローカルパスがないか確認する。
- PC／モバイル、検索、ライト／ダーク、リンク、コード表示を確認する。

[検証記録](./verification.md) · [ライセンス確認](./credits.md)
