#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>

/// <summary>
/// �R���|�[�l���g�֘A
/// </summary>
namespace component
{
    class ComponentBase;

    /// <summary>
    /// �R���|�[�l���g���Ǘ�����
    /// </summary>
    class ComponentManager final
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        ComponentManager() = default;

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~ComponentManager() = default;

        /// <summary>
        /// �X�V����
        /// </summary>
        /// <param name="_deltaTime">�f���^�^�C��</param>
        void Update(const float& _deltaTime);

        /// <summary>
        /// �R���|�[�l���g�ǉ�
        /// </summary>
        /// <typeparam name="T">�R���|�[�l���g��</typeparam>
        /// <typeparam name="...Args">�����Q</typeparam>
        /// <param name="...args">�����Q</param>
        /// <returns>�ǉ������R���|�[�l���g</returns>
        template<typename T, typename... Args>
        std::shared_ptr<T> AddComponent(Args&&... _args)
        {
            auto component = std::make_shared<T>(std::forward<Args>(_args)...);
            components[typeid(T)] = component;
            return component;
        }

        /// <summary>
        /// �R���|�[�l���g�̎擾
        /// </summary>
        /// <typeparam name="T">�擾�Ώۂ̃R���|�[�l���g��</typeparam>
        /// <returns>�R���|�[�l���g</returns>
        template<typename T>
        std::shared_ptr<T> GetComponent()
        {
            if (HasComponent<T>())
            {
                return std::dynamic_pointer_cast<T>(components[typeid(T)]);
            }
            return nullptr;
        }

        /// <summary>
        /// �R���|�[�l���g�̑��݊m�F
        /// </summary>
        /// <typeparam name="T">�m�F�Ώۂ̃R���|�[�l���g</typeparam>
        /// <returns>���݂��邩�ǂ���</returns>
        template<typename T>
        bool HasComponent()
        {
            return components.find(typeid(T)) != components.end();
        }

        /// <summary>
        /// �R���|�[�l���g�폜
        /// </summary>
        /// <param name="component">�폜����R���|�[�l���g</param>
        template<typename T>
        void RemoveComponent()
        {
            components.erase(typeid(T));
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<component::ComponentBase>> components;   //�R���|�[�l���g�Q
    };
}
