#include "ColliderManager.h"
#include "RectCollider/RectCollider.h"
#include "TileCollider/TileCollider.h"

namespace col2d
{
    ColliderID ColliderManager::CreateID()
    {
        ColliderID cID{};

        // 未使用のコライダーのインデックスがあれば再利用し世代も新規にする
        if (!freeIndex.empty())
        {
            cID.index = freeIndex.front();
            freeIndex.pop();
            cID.generation = 0;
        }
        else
        {
            // 新しいコライダーのインデックスを割り当てる
            cID.index = static_cast<uint32_t>(colliders.size());
            cID.generation = 0;
        }

        return cID;
    }

    void ColliderManager::DestroyCollider(const ColliderID& _cID)
    {
        // コライダーのインデックスを解放
        if (colliders.contains(_cID.index))
        {
            colliders.erase(_cID.index);
            freeIndex.push(_cID.index);
        }
    }

    

    void ColliderManager::Step()
    {
        // コライダーの更新処理
        for (auto& [index, collider] : colliders)
        {
            for (auto& otherCollider : colliders)
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
                    collider->ColliderWidth(*otherCollider.second);
                }
            }
        }
    }
    
}
