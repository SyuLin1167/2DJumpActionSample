export module Object.GameObject;

import <memory>;
import <typeindex>;
import <functional>;
import <unordered_map>;

export import MyLib.Math.PropVector2;
export import ObjectState;
export import ObjectTag;
export import AppContext;
export import ObjectContext;
export import Component.ComponentManager;

using namespace math;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    /// <summary>
    /// ゲーム内オブジェクトの基底クラス
    /// </summary>
    export class GameObject
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
        /// 後更新
        /// </summary>
        virtual void LateUpdate() {};

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
            return m_state;
        };

        /// <summary>
        /// 座標(アクセッサー)
        /// </summary>
        /// <returns>座標(外部用)</returns>
        PropVector2<float> AccessPos()
        {
            return PropVector2<float>(m_pos);
        }

        /// <summary>
        /// 速度(アクセッサー)
        /// </summary>
        /// <returns>速度(外部用)</returns>
        PropVector2<float> AccessVel()
        {
            return PropVector2<float>(m_velocity);
        }

        /// <summary>
        /// 自身のタグを取得
        /// </summary>
        /// <returns>自身のタグ</returns>
        virtual ObjectTag MyObjectTag() const = 0;

    protected:
        std::shared_ptr<component::ComponentManager> m_compMgr;   //コンポーネントマネージャー
        const float& m_deltaTime;             //デルタタイム
        Vector2f m_pos;           //座標
        Vector2f m_velocity;      //速さ
        uint32_t m_state;         //状態
    };
}