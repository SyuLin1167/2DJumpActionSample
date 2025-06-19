#pragma once
#include <memory>
#include <unordered_map>
#include <stack>
#include "Graph/Graph.h"

namespace gameSystem
{
    class FrameRate;
}

/// <summary>
/// シーン関連
/// </summary>
namespace scene
{
    class SceneBase;

    /// <summary>
    /// シーンを管理する
    /// </summary>
    class SceneManager final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        SceneManager();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~SceneManager() = default;

        /// <summary>
        /// シーンのループ処理
        /// </summary>
        void GameLoop();

    private:
        /// <summary>
        /// シーンの更新処理
        /// </summary>
        void Update();

        /// <summary>
        /// シーンの描画処理
        /// </summary>
        void Draw();

        /// <summary>
        /// シーンの切り替え処理
        /// </summary>
        void ChangeScene();

        std::stack<std::shared_ptr<SceneBase>> nowScene;     //現在のシーン
        std::shared_ptr<SceneBase> nextScene;                   //次シーン
        std::unique_ptr<class asset::Graph> graph;
    };
}