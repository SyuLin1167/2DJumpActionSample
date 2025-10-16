module Collider.ColliderManager;

namespace col2d
{
    ColliderID ColliderManager::CreateID()
    {
        ColliderID cID{};

        // 未使用のコライダーのインデックスがあれば再利用し世代も新規にする
        if (!m_freeIndexes.empty())
        {
            cID.index = m_freeIndexes.front();
            m_freeIndexes.pop();
            cID.generation = 0;
        }
        else
        {
            // 新しいコライダーのインデックスを割り当てる
            cID.index = static_cast<uint32_t>(m_colliders.size());
            cID.generation = 0;
        }

        return cID;
    }

    void ColliderManager::DestroyCollider(const ColliderID& id)
    {
        // コライダーのインデックスを解放
        if (auto it = m_colliders.find(id.index); it != m_colliders.end()) {
            m_colliders.erase(it);
            m_freeIndexes.push(id.index);
        }
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
        }
    }
    
}
