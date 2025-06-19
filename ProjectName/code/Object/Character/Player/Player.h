#pragma once
#include "GameObject/GameObject.h"

/// <summary>
/// オブジェクト関連
/// </summary>
namespace object
{
    /// <summary>
    /// プレイヤーの役割
    /// </summary>
    class Player final :public GameObject
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
    };
}