・ｿmodule Object.ObjectManager;
import ObjectContext;
import GameSystem.Camera;

namespace object
{
    ObjectManager::ObjectManager()
        : objects()
        , pendingObjects()
        , isUpdate(false)
    {
        ObjCtx::Activate();
    }

    ObjectManager::~ObjectManager() = default;

    void ObjectManager::RemoveObject(class GameObject* object)
    {
        ObjectTag tag = object->MyObjectTag();

        //繧ｪ繝悶ず繧ｧ繧ｯ繝医ｒ蜑企勁
        auto iter = std::find_if(objects[tag].begin(), objects[tag].end(), [object](const std::shared_ptr<GameObject>& ptr) { return ptr.get() == object; });
        if (iter != objects[tag].end())
        {
            objects[tag].erase(iter);
        }
    }

    void ObjectManager::InitBeforeUpdate()
    {
        //閾ｪ霄ｫ縺ｫ蠢・ｦ√↑繧ｪ繝悶ず繧ｧ繧ｯ繝医ｒ蜿門ｾ・        for (auto tag : OBJECT_TAGS)
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
            //繧ｪ繝悶ず繧ｧ繧ｯ繝医ｒ譖ｴ譁ｰ
            for (auto& object : objects[tag])
            {
                object->UpdateComponents();
                object->Update();
            }
        }

        //蠖薙◆繧雁愛螳壹・譖ｴ譁ｰ
        ObjectContext::ColMgr().Step();

        for (auto tag : OBJECT_TAGS)
        {
            for (auto& object : objects[tag])
            {
                object->LateUpdate();
            }
        }
        gameSystem::Camera::Instance().Update();

        // 譖ｴ譁ｰ邨ゆｺ・ｾ後・蜃ｦ逅・        isUpdate = false;
        RefreshObjects();
    }

    void ObjectManager::RefreshObjects()
    {
        for (auto tag : OBJECT_TAGS)
        {
            //豁ｻ莠｡迥ｶ諷九・繧ｪ繝悶ず繧ｧ繧ｯ繝医ｒ蜑企勁
            for (auto& object : objects[tag])
            {
                if (object->NowState() & MainState::DEAD)
                {
                    RemoveObject(object.get());
                }
            }

            //譖ｴ譁ｰ譎ゅ↓霑ｽ蜉縺励◆繧ｪ繝悶ず繧ｧ繧ｯ繝医ｒ驟榊・縺ｫ譬ｼ邏・            if (!pendingObjects.empty())
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
            //繧ｪ繝悶ず繧ｧ繧ｯ繝医ｒ謠冗判
            for (auto& object : objects[tag])
            {
                object->Draw();
            }
        }
    }
}