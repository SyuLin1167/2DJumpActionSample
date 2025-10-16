export module Object.Player;

import Object.GameObject;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    /// <summary>
    /// プレイヤーの役割
    /// </summary>
    export class Player final :public GameObject
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Player();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Player() = default;

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
        void LateUpdate() override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() override;

        /// <summary>
        /// 自身のタグ
        /// </summary>
        /// <returns>プレイヤー</returns>
        ObjectTag MyObjectTag() const override
        {
            return ObjectTag::PLAYER;
        }

        col2d::ColliderID id;
    };
}