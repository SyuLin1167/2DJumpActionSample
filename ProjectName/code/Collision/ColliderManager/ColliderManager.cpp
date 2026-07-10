module Collider.ColliderManager;

namespace col2d
{
    ColliderID ColliderManager::CreateID()
    {
        ColliderID id{};

        // 未使用のコライダーのインデックスがあれば再利用し世代も新規にする
        if (!m_freeID.empty())
        {
            id = m_freeID.front();
            m_freeID.pop();
            ++id.generation;
        }
        else
        {
            // 新しいコライダーのインデックスを割り当てる
            id.index = static_cast<uint32_t>(m_colliders.size());
            id.generation = 0;
        }

        m_generations[id.index] = id.generation;

        return id;
    }

    void ColliderManager::Destroy(const ColliderID& id)
    {
        // コライダーを解放
        if (auto it = m_colliders.find(id.index); it != m_colliders.end())
        {
            // 他のコライダーからのマスクとイベントを削除
            auto& category = it->second->GetFilter().category;
            for (auto& [index, collider] : m_colliders)
            {
                collider->GetFilter().RemoveMask(category);
                collider->DeleteEvent(category);
            }

            // コライダーを削除してインデックスを再利用可能にする
            m_colliders.erase(it);
            m_generations.erase(id.index);
            m_freeID.push(id);
        }
    }

    Collider* ColliderManager::GetCollider(const ColliderID& id) const
    {
        // 世代が一致するか確認
        auto generation = m_generations.find(id.index);
        if (generation == m_generations.end() || generation->second != id.generation)
        {
            return nullptr;
        }

        // インデックスが存在するか確認
        if (auto it = m_colliders.find(id.index); it != m_colliders.end())
        {
            return it->second.get();
        }

        return nullptr;
    }

    void ColliderManager::Step()
    {
        // コライダーの更新処理
        for (auto& [index, collider] : m_colliders)
        {
            for (auto& otherCollider : m_colliders)
            {
                // 同じコライダー同士の衝突は無視
                if (collider == otherCollider.second)
                {
                    continue;
                }

                // フィルターを確認して衝突判定を行う
                if (collider->GetFilter().HasMask(otherCollider.second->GetFilter().category))
                {
                    // コライダー同士の衝突判定
                    collider->CollideWith(*otherCollider.second);
                }
            }

            collider->AddVelocity();
        }
    }
    
}
