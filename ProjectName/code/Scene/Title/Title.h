#pragma once
#include "SceneBase/SceneBase.h"

namespace debug
{
    class DebugSystem;
}

/// <summary>
/// シーン関連
/// </summary>
namespace scene
{
    /// <summary>
    /// タイトルシーンを担当
    /// </summary>
    class Title final :public SceneBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Title();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Title();

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Init() override {};

        /// <summary>
        /// 更新処理
        /// </summary>
        std::shared_ptr<SceneBase> Update() override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() override;

        /// <summary>
        /// ローディング画面
        /// </summary>
        void DrawLoading() override;
        template<class T>
        static std::shared_ptr<SceneBase> CreateNextScene()
        {
            return std::make_shared<T>();
        }

    private:
        int vs;                 //頂点シェーダーハンドル
        int ps;                 //ピクセルシェーダーハンドル
        VERTEX2DSHADER Vert[6]; //頂点(6個)
    };
}

