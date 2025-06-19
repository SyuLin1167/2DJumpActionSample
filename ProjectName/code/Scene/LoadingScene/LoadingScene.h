#pragma once
#include <typeindex>
#include "SceneBase/SceneBase.h"
#include "Coroutine.h"

namespace task
{
    class Loading;
}

/// <summary>
/// �V�[���֘A
/// </summary>
namespace scene
{
    /// <summary>
    /// ���[�f�B���O�K��
    /// </summary>
    enum LoadPolicy :int8_t
    {
        TRANSITION = 0,         //�V�[���J��
        COROUTINE = 1 << 0,     //�R���[�`��
        PROGRESS = 1 << 1,
        DONE = 1 << 2,          //���ʂ̂�
    };

    /// <summary>
    /// ���[�f�B���O��ʂ�S��
    /// </summary>
    class LoadingScene final :public SceneBase
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        LoadingScene() = default;

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="_policy">�|���V�[</param>
        /// <param name="_nextScene">���V�[����Ԃ��֐�</param>
        /// <param name="_draw">�`�揈��</param>
        LoadingScene(int8_t _policy, std::function<std::shared_ptr<SceneBase>()> _nextScene, std::shared_ptr<SceneBase> _holdScene = nullptr);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~LoadingScene() = default;

        /// <summary>
        /// ����������
        /// </summary>
        void Init() override {};

        /// <summary>
        /// �R���[�`���ǂݍ���
        /// </summary>
        /// <returns>������̃R���[�`��</returns>
        Coroutine LoadCoroutine();

        /// <summary>
        /// �X�V����
        /// </summary>
        std::shared_ptr<SceneBase> Update() override;

        /// <summary>
        /// �`�揈��
        /// </summary>
        void Draw() override;

    private:
        uint8_t policy;                                 //�|���V�[
        std::unique_ptr<task::Loading> loading;         //���[�f�B���O�@�\
        std::shared_ptr<SceneBase> holdScene;           //�ꎞ�m�ۗp�̃V�[��
        std::shared_ptr<SceneBase> nextScene;           //���V�[��
        std::function<std::shared_ptr<SceneBase>()> loadScene;  //���V�[���ǂݍ��ݏ���
        Coroutine coroutine;                            //�R���[�`��
    };
}
