module UI.UIManager;

namespace ui
{
    void UIManager::Destroy(const UIElementID& id)
    {
        // UI要素を解放
        m_elements.erase(id.index);
        m_generations.erase(id.index);
        m_freeID.push(id);
    }

    void UIManager::Update()
    {
        for (auto& element : m_elements)
        {
            element.second->Update();
        }
    }

    void UIManager::Draw()
    {
        for (auto& element : m_elements)
        {
            element.second->Draw();
        }
    }

    UIElementID UIManager::CreateID()
    {
        UIElementID id{};

        // 未使用のインデックスがあれば再利用し世代も新規にする
        if (!m_freeID.empty())
        {
            id = m_freeID.front();
            ++id.generation;
            m_freeID.pop();
        }
        else
        {
            // 新しいインデックスを割り当てる
            id.index = static_cast<uint32_t>(m_elements.size());
            id.generation = 0;
        }

        m_generations[id.index] = id.generation;
        return id;
    }
}