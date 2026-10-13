# Modulesと依存関係

## 公開する単位

`.ixx`に`export module`と公開宣言を置き、`.cpp`に`module`を指定して実装を分ける構成です。例えばComponentManagerは`Component.ComponentManager`としてimportします。すべてのコードがこの分割方式に統一されているわけではなく、インライン実装もあります。

```cpp
import Object.GameObject;
import Component.MoveWithKey;
```

呼び出し側は機能のモジュール名を明示します。`export import`は依存先を利用側にも再公開します。一方、ファイルシステム上のフォルダー名とモジュール名は完全一致しません。例えばComponentBaseのモジュール名は`Component`です。

## 外部ヘッダーとの境界

DxLibやWindowsヘッダーは`module;`のグローバルモジュールフラグメントでincludeする例があります。標準ライブラリには`import <memory>;`などのヘッダーユニットも使われています。

## 利点と制約

公開単位と依存関係をコードで追える点は教材になります。ただしビルド時間の短縮は測定していません。Visual Studioのモジュール依存スキャンとプロジェクト登録が必要で、新規ファイルを置くだけではビルド対象になりません。

[全モジュール索引](../api/modules.md)でモジュール名とファイルを対応付けています。
