#pragma once
#include "AssetBase/AssetBase.h"

/// <summary>
/// �A�Z�b�g�֘A
/// </summary>
namespace asset
{
    /// <summary>
    /// �摜�̊Ǘ���S��
    /// </summary>
    class Graph final :public AssetBase
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Graph();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Graph();

        /// <summary>
        /// �n���h������
        /// </summary>
        /// <param name="_handleName">�n���h����</param>
        /// <param name="_graphName">�摜��</param>
        void CreateHandle(std::string _handleName, std::string _graphName) override;

        /// <summary>
        /// �n���h���폜
        /// </summary>
        /// <param name="_name">�폜����n���h����</param>
        void DeleteHandle(std::string _name) override;

        /// <summary>
        /// �n���h���擾
        /// </summary>
        /// <param name="_name">�擾����n���h����</param>
        /// <returns>�n���h��</returns>
        int GetHandle(std::string _name) const 
        {
            return  handles.at(_name);
        }
    private:
        std::unordered_map<std::string, int> handles;   //�n���h���Q
    };
}

