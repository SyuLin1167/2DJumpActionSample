#pragma once
#include <optional> 
#include "ColliderManager/ColliderManager.h"
#include "Collider/ColliderDef.h"

/// <summary>
/// オブジェクト関連
/// </summary>
namespace object
{
    /// <summary>
    /// オブジェクトコンテキスト
    /// </summary>
    struct ObjectContext final
    {
        static void Activate()
        {
            colMgr.emplace();
        }

        static void Deactivate()
        {
            colMgr.reset();
        }

        static col2d::ColliderManager& ColMgr()
        {
            return *colMgr;
        }

    private:
        inline static std::optional<col2d::ColliderManager> colMgr{};
    };

    using ObjCtx = ObjectContext;
}