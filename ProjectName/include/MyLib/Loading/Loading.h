#pragma once
#include <memory>
#include <unordered_map>
#include <array>
#include <vector>
#include <functional>
#include <future>
#include <atomic>

/// <summary>
/// �^�X�N�֘A
/// </summary>
namespace task
{
    /// <summary>
    /// �ǂݍ��݃��x��
    /// </summary>
    enum Level :int16_t
    {
        DATA,
        GRAPH,
        SOUND,
        INIT,
        END,
    };

    /// <summary>
    /// ���[�f�B���O�Ɋւ���@�\(�񓯊�)
    /// </summary>
    class Loading final
    {
    public:

        struct Info
        {
            std::atomic<int> totalTasks;
            std::atomic<int> finishTasks;//�I���^�X�N
            std::promise<void> promise;
            std::shared_future<void> future = promise.get_future().share();
            std::vector<std::future<void>> tasks;
        };

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Loading();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Loading();

        void StartLoading()
        {
            isLoading = true;
        }

        /// <summary>
        /// �^�X�N�̒ǉ�
        /// </summary>
        /// <param name="_level">�ǂݍ��݃��x��</param>
        /// <param name="_task">�ǉ�����^�X�N</param>
        void AddTask(Level _level, std::function<void()> _task);

        /// <summary>
        /// �i���x�̊Ď�
        /// </summary>
        void WatchProgress();

        /// <summary>
        /// ���[�f�B���O�����ǂ���
        /// </summary>
        /// <returns>���[�f�B���O��</returns>
        bool IsLoading() const
        {
            return isLoading;
        }

        /// <summary>
        /// ���݂̐i���x
        /// </summary>
        /// <returns>�i���x</returns>
        float NowProgress() const
        {
            return progress;
        }

    private:
        bool isLoading;                         //���[�f�B���O��
        std::unordered_map<Level, Info> taskInfo;   //�^�X�N
        float progress;                         //�i���x
    };
}

