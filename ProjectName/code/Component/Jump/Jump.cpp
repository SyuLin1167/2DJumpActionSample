#include "Jump.h"
#include "GameObject/GameObject.h"

using namespace math;

namespace component
{
    Jump::Jump(object::GameObject* _owner, std::function<bool()> _trriger)
        :ComponentBase(_owner)
        , m_nowJump(false)
        , m_trriger(_trriger)
    {
        //�����Ȃ�
    }

    void Jump::Update(const float& _deltaTime)
    {
        //�g���K�[�������ꂽ��W�����v�����{
        if (m_trriger())
        {
            TryJump();
        }
        
        //�ő嗎�����x�܂ŏd�͂����Z����
        if (owner->AccessVel().NowY() < MAX_FALL_VELOCITY)
        {
            owner->AccessVel().Add(PropVector2<float>::Y, FALL_SPEED * GRAVITY * _deltaTime);
        }
    }

    void Jump::TryJump()
    {
        //�W�����v���łȂ���΃W�����v�����{
        if (!m_nowJump)
        {
            m_nowJump = true;
            owner->AccessVel().Assign(PropVector2<float>::Y, 0.0f);
            owner->AccessVel().Add(PropVector2<float>::Y, JUMP_POWER);
        }
    }
}
