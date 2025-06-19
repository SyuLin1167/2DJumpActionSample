#pragma once
#include <memory>

/// <summary>
/// オブジェクト関連
/// </summary>
namespace object
{
    class ObjectManager;
}

/// <summary>
/// シーン関連
/// </summary>
namespace scene
{
    /// <summary>
    /// シーンの基底クラス
    /// </summary>
    class SceneBase: public std::enable_shared_from_this<SceneBase>
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        SceneBase();

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~SceneBase();

        /// <summary>
        /// 初期化処理
        /// </summary>
        virtual void Init() = 0;

        /// <summary>
        /// 更新処理
        /// </summary>
        virtual std::shared_ptr<SceneBase> Update() = 0;

        /// <summary>
        /// 描画処理
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// ローディング画面描画処理
        /// </summary>
        virtual void DrawLoading() {};
        
    protected:
        std::unique_ptr<object::ObjectManager> objManager;        //オブジェクト管理のインスタンス
    };
}