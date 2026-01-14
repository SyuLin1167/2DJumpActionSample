export module UI.UIManager;

import UI.UIBase;
import MyLib.MouseStatus;
import <unordered_map>;
import <memory>;
import <queue>;
import <algorithm>;

/// <summary>
/// UI関連
/// </summary>
export namespace ui
{
    /// <summary>
    /// UI要素の識別子
    /// </summary>
    export struct UIElementID
    {
        uint32_t index;          // インデックス
        uint16_t generation;     // 生成世代
    };

    /// <summary>
    /// UI要素管理
    /// </summary>
    export class UIManager
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        UIManager() = default;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~UIManager() = default;

        /// <summary>
        /// UI要素を生成
        /// </summary>
        /// <typeparam name="T">生成するUI要素の型</typeparam>
        /// <param name="args">コンストラクタ引数</param>
        /// <returns>生成されたUI要素の識別子</returns>
        template<typename T, typename... Args>
        UIElementID Create(Args&&... args)
        {
            UIElementID id = CreateID();
            auto element = std::make_unique<T>(std::forward<Args>(args)...);
            m_elements[id.index] = std::move(element);
            return id;
        }

        /// <summary>
        /// UI要素を取得
        /// </summary>
        /// <param name="id">検索する要素の識別子</param>
        /// <returns>UI要素の識別子</returns>
        UIBase* GetElement(const UIElementID& id)
        {
            // 世代が一致するか確認
            auto generation = m_generations.find(id.index);
            if (generation == m_generations.end() || generation->second != id.generation)
            {
                return nullptr;
            }

            // インデックスが存在するか確認
            if (auto it = m_elements.find(id.index); it != m_elements.end())
            {
                return it->second.get();
            }
            return nullptr;
        }

        /// <summary>
        /// UI要素を破棄
        /// </summary>
        /// <param name="id">UI要素の識別子</param>
        void Destroy(const UIElementID& id);

        /// <summary>
        /// UI要素をクリア
        /// </summary>
        void Clear()
        {
            m_elements.clear();
        }

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update();

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw();

    private:
        /// <summary>
        /// UI要素の識別子を生成
        /// </summary>
        /// <returns>生成されたUI要素の識別子</returns>
        UIElementID CreateID();

        std::queue<UIElementID> m_freeID; // 未使用のUI要素のID
        std::unordered_map<uint32_t, uint16_t> m_generations; // 現在の世代を管理
        std::unordered_map<uint32_t, std::unique_ptr<UIBase>> m_elements; // UI要素のマップ
    };
}
