---
layout: home
hero:
  name: 2DGameSample
  text: 仕組みを知って、ゲームをつくる。
  tagline: C++20 ModulesとDxLibで学ぶ、2Dゲーム開発の基礎と設計。
  actions:
    - theme: brand
      text: まずは動かしてみる
      link: /guide/quickstart
    - theme: alt
      text: 実習を始める
      link: /tutorials/
    - theme: alt
      text: APIを調べる
      link: /api/
features:
  - title: 機能を組み合わせる
    details: GameObjectに移動・アニメーション・音声などのComponentを追加して、ゲームの動作を組み立てます。
    link: /architecture/components
  - title: 動作の流れを理解する
    details: 入力、更新、衝突、描画、シーン切り替えを追い、ゲームループの役割を学びます。
    link: /guide/lifecycle
  - title: 設計と制約を読む
    details: Visitor、非同期読み込み、所有権と寿命の工夫を、実装とその制約から説明します。
    link: /architecture/
---

## このドキュメントについて

対象はC++のクラス・継承・参照・ポインタの基本を学んだ方です。スマートポインタやModulesは必要な箇所で補足します。

付属のジャンプアクションは利用例です。共通機能をほかの2Dゲームへ応用することを目指します。最初に[対応範囲と既知の制約](./project/status.md)を確認してください。

コード確認基準は`develop-dxlib`の`08f9fa53`（2026-10-12）です。説明・実習コードはソースと照合していますが、今回の文書整備ではC++のビルド・ゲーム動作は未検証です。[検証記録](./project/verification.md)
