#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "AssetBase/AssetBase.h"

/// <summary>
/// �A�Z�b�g�֘A
/// </summary>
namespace asset
{
    /// <summary>
    /// �A�Z�b�g�S�ʂ��Ǘ�����
    /// </summary>
    class AssetManager final
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        AssetManager() = default;

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~AssetManager() = default;

        /// <summary>
        /// �A�Z�b�g�ǂݍ���
        /// </summary>
        /// <typeparam name="T">�A�Z�b�g�̎��</typeparam>
        /// <typeparam name="...Args">����</typeparam>
        /// <param name="_name">�A�Z�b�g��</param>
        /// <param name="_path">�t�@�C���p�X</param>
        /// <param name="..._args">�����Q</param
        template<typename T, typename... Args>
        void Load(std::string _name, std::string _path, Args&&... _args)
        {
            if (registry.find(typeid(T)) == registry.end())
            {
                registry[typeid(T)] = std::make_unique<T>(std::forward<Args>(_args)...);
            }
            registry.at(typeid(T))->CreateHandle(_name, _path);
        }

        /// <summary>
        /// �t�F�b�`
        /// </summary>
        /// <typeparam name="T">�A�Z�b�g�̎��</typeparam>
        /// <returns>�A�Z�b�g</returns>
        template<typename T>
        T* Fetch()
        {
            auto it = registry.find(typeid(T));
            if (it != registry.end())
            {
                return static_cast<T*>(it->second.get());
            }
            return nullptr;
        }

        /// <summary>
        /// �A�Z�b�g�폜
        /// </summary>
        /// <typeparam name="T">�A�Z�b�g�̎��</typeparam>
        /// <param name="_name">�A�Z�b�g��</param>
        template<typename T>
        void Delete(std::string _name)
        {
            registry.at(typeid(T))->DeleteHandle(_name);
        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<AssetBase>> registry;   //�A�Z�b�g�o�^�Q
    };
}
