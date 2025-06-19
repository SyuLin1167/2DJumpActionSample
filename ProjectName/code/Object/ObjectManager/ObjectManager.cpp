#include "ObjectManager.h"
#include "GameObject/GameObject.h"

namespace object
{
    ObjectManager::ObjectManager()
        : objects()
        , pendingObjects()
        , isUpdate(false)
    {
        //処理なし
    }

    void ObjectManager::AddObject(class GameObject* object)
    {
        //更新中なら一時保存、そうでなければオブジェクト配列に追加
        if (isUpdate)
        {
            pendingObjects.emplace_back(object);
            return;
        }
        objects[object->MyObjectTag()].emplace_back(object);
    }

    void ObjectManager::RemoveObject(class GameObject* object)
    {
        ObjectTag tag = object->MyObjectTag();

        //オブジェクトを削除
        auto iter = std::find_if(objects[tag].begin(), objects[tag].end(), [object](const std::shared_ptr<GameObject>& ptr) { return ptr.get() == object; });
        if (iter != objects[tag].end())
        {
            objects[tag].erase(iter);
        }
    }

    void ObjectManager::InitBeforeUpdate()
    {
        //自身に必要なオブジェクトを取得
        for (auto tag : OBJECT_TAGS)
        {
            for (auto& object : objects[tag])
            {
                object->GetReferenceObject([this](uint32_t tag)
                    {
                        return this->GetObjForTag(tag);
                    });
                object->Init();
            }
        }
    }

    void ObjectManager::Update()
    {
        isUpdate = true;
        for (auto tag : OBJECT_TAGS)
        {
            //オブジェクトを更新
            for (auto& object : objects[tag])
            {
                object->UpdateComponents();
                object->Update();
            }

            //当たり判定の更新
            for (auto& object : objects[tag])
            {
                object->UpdateCollision();
            }
        }
        isUpdate = false;

        for (auto tag : OBJECT_TAGS)
        {
            //死亡状態のオブジェクトを削除
            for (auto& object : objects[tag])
            {
                if (object->NowState() & MainState::DEAD)
                {
                    RemoveObject(object.get());
                }
            }

            //更新時に追加したオブジェクトを配列に格納
            if (!pendingObjects.empty())
            {
                for (auto pendingObj : pendingObjects)
                {
                    objects[pendingObj->MyObjectTag()].emplace_back(pendingObj);
                }
                pendingObjects.clear();
            }
        }
    }

    std::vector<std::shared_ptr<GameObject>> ObjectManager::GetObjForTag(uint32_t tag)
    {
        if (objects.find(tag) != objects.end())
        {
            return objects[tag];
        }
        return {};
    }

    void ObjectManager::Draw()
    {
        for (auto tag : OBJECT_TAGS)
        {
            //オブジェクトを描画
            for (auto& object : objects[tag])
            {
                object->Draw();
            }
        }
    }
}