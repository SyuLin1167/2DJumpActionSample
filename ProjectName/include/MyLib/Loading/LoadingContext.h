#pragma once
#include "Loading.h"

/// <summary>
/// �^�X�N�֘A
/// </summary>
namespace task
{
    /// <summary>
    /// Loading�p�X�R�[�v�R���e�L�X�g
    /// </summary>
    class LoadingContext final
    {
    public:
        /// <summary>
        /// Loading�N���X�̊m��
        /// </summary>
        /// <param name="_loading">�m�ۂ���Loading</param>
        static void Set(Loading* _loading)
        {
            current = _loading;
        }

        /// <summary>
        /// Loading�̎擾
        /// </summary>
        /// <returns>�m�ے���Loading</returns>
        static Loading* Get()
        {
            return current;
        }

        /// <summary>
        /// Loading�̉��
        /// </summary>
        static void Release()
        {
            delete current;
        }
    private:
        static inline thread_local Loading* current = nullptr;  //�m�ے���Loading
    };
}
