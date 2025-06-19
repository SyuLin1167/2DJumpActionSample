#pragma once
#include "AssetBase/AssetBase.h"

/// <summary>
/// �A�Z�b�g�֘A
/// </summary>
namespace asset
{
    /// <summary>
    /// �����摜�̊Ǘ���S��
    /// </summary>
    class DivisionGraph final :public AssetBase
    {
        struct Info;
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        DivisionGraph() = default;

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="_divW">�������鉡��</param>
        /// <param name="_divH">�������闧��</param>
        DivisionGraph(int _divW,int _divH);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~DivisionGraph();

        /// <summary>
        /// �����T�C�Y�ύX
        /// </summary>
        /// <param name="_divW">�������鉡��</param>
        /// <param name="_divH">�������闧��</param>
        void ChangeDivSize(int _divW, int _divH)
        {
            divW = _divW;
            divH = _divH;
        }

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
        /// <param name="_num">�擾����Y����</param>
        /// <returns></returns>
        int GetHandle(std::string _name, int _index) const
        {
            return handles.at(_name).handle[_index];
        };

    private:
        /// <summary>
        /// �n���h�����
        /// </summary>
        struct Info
        {
            int* handle;
            int total;
        };

        int divW;       //������(��)
        int divH;       //������(�c)
        std::unordered_map<std::string, Info> handles;  //�n���h���Q
    };
}
