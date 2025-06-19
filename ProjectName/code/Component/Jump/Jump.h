#pragma once
#include <functional>
#include "ComponentBase/ComponentBase.h"
#include "Math/Vector2.h"

/// <summary>
/// �R���|�[�l���g�֘A
/// </summary>
namespace component
{
    constexpr float GRAVITY = 3.8f;         //�d�͉����x
    constexpr float FALL_SPEED = 5.0f;      //�������x
    constexpr float JUMP_POWER = -8.0f;    //�W�����v��

    /// <summary>
    /// �W�����v����
    /// </summary>
    class Jump final :public ComponentBase
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Jump() = default;

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="owner">���L��</param>
        /// <param name="order">�X�V�̗D�揇��</param>
        Jump(object::GameObject* _owner, std::function<bool()> _trriger);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Jump() = default;

        /// <summary>
        /// �X�V
        /// </summary>
        /// <param name="deltaTime">�f���^�^�C��</param>
        void Update(const float& _deltaTime) override;

        /// <summary>
        /// �W�����v�̎��s
        /// </summary>
        void TryJump();

        /// <summary>
        /// �W�����v�\�ɂ���
        /// </summary>
        void CanJump()
        {
            m_nowJump = false;
        }

    private:
        const float MAX_FALL_VELOCITY = 50.0f;      //�ő嗎�����x
        bool m_nowJump;                             //�W�����v��Ԕ���
        std::function<bool()> m_trriger;            //�g���K�[
    };
}

