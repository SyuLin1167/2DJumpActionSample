#pragma once
#include <typeindex>
#include "SceneBase/SceneBase.h"
#include "Coroutine.h"

namespace task
{
    class Loading;
}

/// <summary>
/// シーン関連
/// </summary>
namespace scene
{
    /// <summary>
    /// ローディング規約
    /// </summary>
    enum LoadPolicy :int8_t
    {
        TRANSITION = 0,         //シーン遷移
        COROUTINE = 1 << 0,     //コルーチン
        PROGRESS = 1 << 1,
        DONE = 1 << 2,          //結果のみ
    };

    /// <summary>
    /// ローディング画面を担当
    /// </summary>
    class LoadingScene final :public SceneBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        LoadingScene() = default;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_policy">ポリシー</param>
        /// <param name="_nextScene">次シーンを返す関数</param>
        /// <param name="_draw">描画処理</param>
        LoadingScene(int8_t _policy, std::function<std::shared_ptr<SceneBase>()> _nextScene, std::shared_ptr<SceneBase> _holdScene = nullptr);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~LoadingScene() = default;

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Init() override {};

        /// <summary>
        /// コルーチン読み込み
        /// </summary>
        /// <returns>生成後のコルーチン</returns>
        Coroutine LoadCoroutine();

        /// <summary>
        /// 更新処理
        /// </summary>
        std::shared_ptr<SceneBase> Update() override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() override;

    private:
        uint8_t policy;                                 //ポリシー
        std::unique_ptr<task::Loading> loading;         //ローディング機能
        std::shared_ptr<SceneBase> holdScene;           //一時確保用のシーン
        std::shared_ptr<SceneBase> nextScene;           //次シーン
        std::function<std::shared_ptr<SceneBase>()> loadScene;  //次シーン読み込み処理
        Coroutine coroutine;                            //コルーチン
    };
}
