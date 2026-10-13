# 導入・ビルド・実行

## 1. ソースを取得する

[環境構築](./environment.md)を終えてから、保存したいフォルダーで次を実行します。

```powershell
git clone --branch develop-dxlib https://github.com/SyuLin1167/2DGameSample.git
cd 2DGameSample
```

既存の作業フォルダーを使う場合は、変更を保管してから対象ブランチを確認してください。最新版と文書の確認基準は異なる場合があります。[検証記録](../project/verification.md)に基準コミットを記載しています。

## 2. ライブラリを取得する

```powershell
.\setup.bat
```

相対パスを使うスクリプトなので、必ずリポジトリ直下で実行します。DxLibとnlohmann/jsonをダウンロード・展開し、最後にソリューションを開く構成です。

完了表示だけでなく、`ProjectName/include/DxLib`と`ProjectName/include/nlohmann/json.hpp`が存在することを確認します。再実行するとnlohmannフォルダーを作り直すため、外部ライブラリに独自変更を置かないでください。

## 3. ソリューションを開く

`ProjectName/2DGameSample.sln`をVisual Studioで開きます。構成は`Debug`、プラットフォームは`x64`を選びます。ツールセット更新を提案されても、ガイドの基準はv143です。

「ビルド → ソリューションのビルド」を実行し、成功したらデバッグを開始します。初回実行のためにソリューションやプロジェクト名を変更する必要はありません。

## 4. 起動を確認する

期待する結果はタイトル画面とStart／Exitボタンの表示です。Startからプレイへ進み、[操作方法](./controls.md)で移動を試します。これは確認手順であり、今回の文書制作での実機検証結果ではありません。

## リソースと配布

`Execution`は実行ファイルの場所を起点に`../../resources`を探し、実行ファイル横の`resources`へコピーします。開発中は元の`ProjectName/resources`を編集してください。出力先だけ編集すると次の起動で上書きされます。

コピー元がない場合は例外になる実装です。実行ファイルとresourcesだけを別フォルダーへ持ち出す配布方法は、現状の起動処理に対して別途検証・対応が必要です。

根拠：[Execution.cpp](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/GameSystem/Execution/Execution.cpp)
