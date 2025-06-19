#pragma once
#include "SceneBase/SceneBase.h"

namespace debug
{
    class DebugSystem;
}

/// <summary>
/// �V�[���֘A
/// </summary>
namespace scene
{
    /// <summary>
    /// �^�C�g���V�[����S��
    /// </summary>
    class Title final :public SceneBase
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Title();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Title();

        /// <summary>
        /// ����������
        /// </summary>
        void Init() override {};

        /// <summary>
        /// �X�V����
        /// </summary>
        std::shared_ptr<SceneBase> Update() override;

        /// <summary>
        /// �`�揈��
        /// </summary>
        void Draw() override;

        /// <summary>
        /// ���[�f�B���O���
        /// </summary>
        void DrawLoading() override;
        template<class T>
        static std::shared_ptr<SceneBase> CreateNextScene()
        {
            return std::make_shared<T>();
        }

    private:
        int vs;                 //���_�V�F�[�_�[�n���h��
        int ps;                 //�s�N�Z���V�F�[�_�[�n���h��
        VERTEX2DSHADER Vert[6]; //���_(6��)
    };
}

