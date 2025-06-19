#pragma once
#include <iostream>
#include <coroutine>
#include <functional>
#include <variant>

/// <summary>
/// �ҋ@����
/// </summary>
struct WaitForSeconds
{
    float seconds;                  //�ҋ@����b��
};

/// <summary>
/// �ҋ@����
/// </summary>
struct WaitUntil
{
    std::function<bool()> pred;     //�ҋ@���鏈��
};

using YieldType = std::variant<std::monostate, WaitForSeconds, WaitUntil>;      //co_yield�̑ҋ@�pvariant

/// <summary>
/// �R���[�`��
/// </summary>
struct Coroutine
{
    struct promise_type;

    // �R�s�[�֎~
    Coroutine(const Coroutine&) = delete;
    Coroutine& operator=(const Coroutine&) = delete;

    //std::move�̂݋�����
    Coroutine(Coroutine&& other) noexcept : handle(other.handle)
    {
        other.handle = nullptr;
    }
    Coroutine& operator=(Coroutine&& other) noexcept
    {
        if (this != &other) {
            if (handle) handle.destroy();
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Coroutine() : handle(nullptr) {};

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="h">�쐬����coroutine_handle</param>
    Coroutine(std::coroutine_handle<promise_type> _handle) : handle(_handle) {}

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Coroutine()
    {
        if (handle)
        {
            handle.destroy();
        }
    }

    /// <summary>
    /// �R���[�`���W�J�p���[��
    /// </summary>
    struct promise_type
    {
        /// <summary>
        /// �Ԋ҃I�u�W�F�N�g�擾
        /// </summary>
        /// <returns>Coroutin�^�I�u�W�F�N�g</returns>
        Coroutine get_return_object()
        {
            return { std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        /// <summary>
        /// �R���[�`���J�n����
        /// </summary>
        /// <returns>suspend���</returns>
        std::suspend_always initial_suspend()
        {
            return {};
        }

        /// <summary>
        /// �R���[�`���I������
        /// </summary>
        /// <returns>suspend���</returns>
        std::suspend_always final_suspend() noexcept
        {
            return {};
        }

        /// <summary>
        /// co_return�Ăяo���p
        /// </summary>
        void return_void() {}

        /// <summary>
        /// co_yield�Ăяo���p
        /// </summary>
        /// <param name="">�ҋ@�p���[��</param>
        std::suspend_always yield_value(YieldType _yT)
        {
            yieldType = _yT;
            return {};
        }

        /// <summary>
        /// ��O����������
        /// </summary>
        void unhandled_exception()
        {
            throw;
        }

        YieldType yieldType;    //yield��
    };

    /// <summary>
    /// 1�X�e�b�v�i�߂�
    /// </summary>
    /// <returns>�s�i�\��</returns>
    bool resume() const
    {
        if (!handle || handle.done())
        {
            return false;
        }
        handle.resume();
        return !handle.done();
    }

    /// <summary>
    /// �ҋ@�w���̊m�F
    /// </summary>
    /// <returns>�ҋ@�w��</returns>
    YieldType get_yield_type() const
    {
        return handle.promise().yieldType;
    }

    std::coroutine_handle<promise_type> handle;     //resume()�p�n���h��
};