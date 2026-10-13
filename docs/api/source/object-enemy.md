# Object.Enemy

オブジェクト関連 / 敵の役割

所属：[objectのAPI解説](../object.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/Object/Character/Enemy/Enemy.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/Object/Character/Enemy/Enemy.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module Object.Enemy;

import Object.GameObject;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    constexpr float MAX_HEALTH = 1.0f;  // 最大体力

    /// <summary>
    /// 敵の役割
    /// </summary>
    export class Enemy final :public GameObject
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Enemy();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Enemy();

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Init() override;

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update() override;

        /// <summary>
        /// 後更新処理
        /// </summary>
        void LateUpdate() override {};

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() override;

        /// <summary>
        /// 自身のタグ
        /// </summary>
        /// <returns>敵</returns>
        ObjectTag MyObjectTag() const override
        {
            return ObjectTag::ENEMY;
        }

    private:
        col2d::ColliderID id;   // コライダーID
        float m_health;        // 体力
        float m_damage;        // ダメージ
    };
}
```
