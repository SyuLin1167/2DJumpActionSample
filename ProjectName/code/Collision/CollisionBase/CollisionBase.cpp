#include "CollisionBase.h"
#include"RectCollision/RectCollision.h"
#include"MapCollision/MapCollision.h"

namespace collision
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CollisionBase::CollisionBase()
        : targetColInfo()
    {
        //処理なし
    }

    void CollisionBase::AddTargetCollision(uint32_t _object, uint32_t _shape, std::function<void()> _event, bool _isTrriger)
    {
        //対象の当たり判定情報を追加
        uint64_t filter = (static_cast<uint64_t>(_object) << 32) | _shape;
        targetColInfo[filter].isTrriger = _isTrriger;
        if (_event)
        {
            targetColInfo[filter].events.push_back(_event);
        }
    }
}
