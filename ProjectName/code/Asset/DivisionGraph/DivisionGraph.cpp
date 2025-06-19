#include <DxLib.h>
#include <format>
#include "DivisionGraph.h"
#include "FileIO/ExeFilePath.h"

namespace asset
{
    DivisionGraph::DivisionGraph(int _divW, int _divH)
        : divW(_divW)
        , divH(_divH)
        , handles()
    {
        //�����Ȃ�
    }

    DivisionGraph::~DivisionGraph()
    {
        //�m�ۂ����摜�̉��
        for (auto& info : handles)
        {
            for (int i = 0; i < info.second.total; i++)
            {
                DeleteGraph(info.second.handle[i]);
            }
        }
    }

    void DivisionGraph::CreateHandle(std::string _handleName, std::string _graphName)
    {
        //�摜�̏������W
        auto fpath = file::GetExeDirectory() / std::format("assets/{}", _graphName);
        int img = LoadGraph(fpath.string().c_str());
        int imgW, imgH;
        GetGraphSize(img, &imgW, &imgH);
        DeleteGraph(img);
        int col = imgW / divW;
        int row = imgH / divH;
        handles[_handleName].total = col * row;
        handles[_handleName].handle = new int[handles[_handleName].total];

        //�擾������񂩂�摜�����ǂݍ���
        LoadDivGraph(fpath.string().c_str(), handles[_handleName].total, col, row, divW, divH, handles[_handleName].handle);
    }

    void DivisionGraph::DeleteHandle(std::string _name)
    {
        //�n���h�����������č폜
        auto it = handles.find(_name);
        if (it == handles.end())
        {
            return;
        }

        for (int i = 0; i < it->second.total; ++i)
        {
            DeleteGraph(it->second.handle[i]);
        }

        delete[] it->second.handle;
        handles.erase(it);
    }
}