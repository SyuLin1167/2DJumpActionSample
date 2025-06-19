#include "CollisionManager.h"
#include "GameObject/GameObject.h"
#include "GameObject/ObjectTag.h"

namespace collision
{
    CollisionManager::CollisionManager(object::GameObject* _owner)
        : collisions()
    {
        allCollision[_owner] = this;
    }

    CollisionManager::~CollisionManager()
    {
        //全当たり判定から自身を削除
        auto iter = std::find_if(allCollision.begin(), allCollision.end(), [this](const auto& pair) {
            return pair.second == this;
        });
        if (iter != allCollision.end())
        {
            allCollision.erase(iter);
        }
    }

    void CollisionManager::ColliderWith()
    {
        //全当たり判定を実施
        for (auto& collision : collisions)
        {
            //判定対象のオブジェクトがあるか一通り検索
            for (uint32_t objTag : object::OBJECT_TAGS)
            {
                //なければ次へスキップ
                if (!collision->HasTargetCollision(static_cast<uint64_t>(objTag) << 32))
                {
                    continue;
                }

                //あれば次は形状があるか一通り検索
                for (uint32_t shapeTag : SHAPE_TAGS)
                {
                    //なければ次へスキップ
                    if (!collision->HasTargetCollision(shapeTag))
                    {
                        continue;
                    }

                    //判定対象の当たり判定があれば処理を実施
                    for (auto& targetObj : allCollision)
                    {
                        if (targetObj.first->MyObjectTag() & objTag)
                        {
                            uint64_t handle = (static_cast<uint64_t>(objTag) << 32 | shapeTag);
                            collision->Dispatch(handle, targetObj.second->GetCollision(shapeTag).get());
                        }
                    }
                }
            }
        }
    }
}