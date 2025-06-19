#pragma once
#include "../SceneBase/SceneBase.h"

/// <summary>
/// シーン関連
/// </summary>
namespace scene
{
    /// <summary>
    /// プレイシーンを担当
    /// </summary>
    class Play final :public SceneBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Play();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Play() = default;

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Init() override;

        /// <summary>
        /// 更新処理
        /// </summary>
        std::shared_ptr<SceneBase> Update() override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() override;
    };
}
