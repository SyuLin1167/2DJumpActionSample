#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include <typeindex>
#include "Math/PropVector2.h"
#include "ObjectTag.h"
#include "ObjectState.h"
#include "AssetManager/AssetManager.h"
#include "ComponentManager/ComponentManager.h"
#include "CollisionManager/CollisionManager.h"

using namespace math;

/// <summary>
/// オブジェクト関連
/// </summary>
namespace object
{
    /// <summary>
    /// ゲーム内オブジェクトの基底クラス
    /// </summary>
    class GameObject
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        GameObject();

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~GameObject();

        /// <summary>
        ///  参照するオブジェクト取得
        /// </summary>
        virtual void GetReferenceObject(std::function<std::vector<std::shared_ptr<GameObject>>(uint32_t)> referenceObj) {};

        /// <summary>
        /// 初期化処理
        /// </summary>
        virtual void Init() = 0;

        /// <summary>
        /// 更新
        /// </summary>
        virtual void Update() {};

        /// <summary>
        /// 当たり判定更新
        /// </summary>
        void UpdateCollision();

        /// <summary>
        /// コンポーネント更新
        /// </summary>
        void UpdateComponents();

        /// <summary>
        /// 描画
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// 現在の状態
        /// </summary>
        /// <returns>状態</returns>
        uint32_t NowState() const
        {
            return state;
        };

        /// <summary>
        /// 座標(アクセッサー)
        /// </summary>
        /// <returns>座標(外部用)</returns>
        PropVector2<float> AccessPos()
        {
            return PropVector2<float>(pos);
        }

        /// <summary>
        /// 速度(アクセッサー)
        /// </summary>
        /// <returns>速度(外部用)</returns>
        PropVector2<float> AccessVel()
        {
            return PropVector2<float>(velocity);
        }

        /// <summary>
        /// 自身のタグを取得
        /// </summary>
        /// <returns>自身のタグ</returns>
        virtual ObjectTag MyObjectTag() const = 0;

    protected:
        std::unique_ptr<asset::AssetManager> assetMgr;          //アセットマネージャー
        std::shared_ptr<component::ComponentManager> compMgr;   //コンポーネントマネージャー
        std::shared_ptr<collision::CollisionManager> colMgr;    //コリジョンマネージャー
        const float& deltaTime;             //デルタタイム
        Vector2<float> pos;           //座標
        Vector2<float> size;          //サイズ
        Vector2<float> velocity;      //速さ
        uint32_t state;                     //状態
    };
}