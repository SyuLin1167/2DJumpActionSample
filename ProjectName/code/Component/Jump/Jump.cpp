#include "Jump.h"
#include "GameObject/GameObject.h"

using namespace math;

namespace component
{
    Jump::Jump(object::GameObject* _owner, std::function<bool()> _trriger)
        :ComponentBase(_owner)
        , nowJump(false)
        , trriger(_trriger)
    {
        //処理なし
    }

    void Jump::Update(const float& _deltaTime)
    {
        //トリガーが引かれたらジャンプを実施
        if (trriger())
        {
            TryJump();
        }
        
        // ジャンプ中なら最大落下速度まで重力を加算する
        if (owner->AccessVel().NowY() < MAX_FALL_VELOCITY)
        {
            owner->AccessVel().Add(PropVector2<float>::Y, FALL_SPEED * GRAVITY * _deltaTime);
        }
    }

    void Jump::TryJump()
    {
        //ジャンプ中でなければジャンプを実施
        if (!nowJump)
        {
            nowJump = true;
            owner->AccessVel().Assign(PropVector2<float>::Y, 0.0f);
            owner->AccessVel().Add(PropVector2<float>::Y, JUMP_POWER);
        }
    }
}
