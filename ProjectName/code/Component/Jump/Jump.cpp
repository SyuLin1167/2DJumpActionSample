module Component.Jump;
import Object.GameObject;
import MyLib.Math.PropVector2;

using namespace math;

namespace component
{
    Jump::Jump(object::GameObject* owner, std::function<bool()> trigger)
        :ComponentBase(owner)
        , m_nowJump(false)
        , m_trigger(trigger)
    {
        //処理なし
    }

    void Jump::Update(const float& deltaTime)
    {
        //トリガーが引かれたらジャンプを実施
        if (m_trigger())
        {
            TryJump();
        }
        
        // ジャンプ中なら最大落下速度まで重力を加算する
        if (m_owner->AccessVel().NowY() < MAX_FALL_VELOCITY)
        {
            m_owner->AccessVel().Add(PropVector2<float>::Y, FALL_SPEED * GRAVITY * deltaTime);
        }
    }

    void Jump::TryJump()
    {
        //ジャンプ中でなければジャンプを実施
        if (!m_nowJump)
        {
            m_nowJump = true;
            m_owner->AccessVel().Assign(PropVector2<float>::Y, 0.0f);
            m_owner->AccessVel().Add(PropVector2<float>::Y, JUMP_POWER);
        }
    }
}
