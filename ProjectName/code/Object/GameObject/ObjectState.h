#pragma once

/// <summary>
/// �I�u�W�F�N�g�֘A
/// </summary>
namespace object
{
    /// <summary>
    /// ���C���X�e�[�^�X
    /// </summary>
    enum MainState :uint32_t
    {
        ACTIVE = 0,           //�A�N�e�B�u���
        PAUSE = 1 << 0,       //��~���
        DEAD = 1 << 1,        //���S���
    };
}
