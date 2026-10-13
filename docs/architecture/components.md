# コンポーネントによる組合せ

PlayerはGameObjectを継承し、ComponentManagerにMoveWithKey、Jump、Animator、AudioSourceを追加します。GameObjectの継承でゲーム内要素の共通契約を作り、Componentで個別の機能を組み合わせる構造です。

## 分けることで読みやすくなる部分

移動のキー設定、ジャンプ判定、アニメーション再生を別クラスで読めます。Playerはそれらの設定と、衝突結果・再生状態の連携を担当します。これは構造上の利点であり、再利用率などの数値を計測したものではありません。

## 更新契約

ComponentBaseは所有者への非所有ポインタを持ち、UpdateにdeltaTimeが渡されます。所有者のAccessPos／AccessVelを通じて値を操作します。Componentを追加した後、ObjectManagerが毎フレーム更新します。

## 制約

ComponentManagerは型をキーにしたunordered_mapです。同型を複数登録して別々に管理する構成ではなく、更新順も追加順に固定されません。データ指向のECSとは説明しません。複数Componentが同じ軸を書き換える場合、役割を分ける必要があります。

[Component API](../api/component.md) · [Component実習](../tutorials/component.md)
