#pragma once
#include <unordered_map>
#include<string>

/// <summary>
/// �A�Z�b�g�֘A
/// </summary>
namespace asset
{
    /// <summary>
    /// �A�Z�b�g�̊��N���X
    /// </summary>
    class AssetBase
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        AssetBase() = default;

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        virtual ~AssetBase() = default;

        /// <summary>
        /// �n���h������
        /// </summary>
        /// <param name="_handleName">�n���h����</param>
        /// <param name="_graphName">�摜��</param>
        virtual void CreateHandle(std::string _handleName, std::string _graphName) = 0;

        /// <summary>
        /// �n���h���폜
        /// </summary>
        /// <param name="_name">�폜����n���h����</param>
        virtual void DeleteHandle(std::string _name) = 0;
    };
}
