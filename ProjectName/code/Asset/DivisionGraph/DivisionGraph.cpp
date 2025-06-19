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
        //処理なし
    }

    DivisionGraph::~DivisionGraph()
    {
        //確保した画像の解放
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
        //画像の情報を収集
        auto fpath = file::GetExeDirectory() / std::format("assets/{}", _graphName);
        int img = LoadGraph(fpath.string().c_str());
        int imgW, imgH;
        GetGraphSize(img, &imgW, &imgH);
        DeleteGraph(img);
        int col = imgW / divW;
        int row = imgH / divH;
        handles[_handleName].total = col * row;
        handles[_handleName].handle = new int[handles[_handleName].total];

        //取得した情報から画像分割読み込み
        LoadDivGraph(fpath.string().c_str(), handles[_handleName].total, col, row, divW, divH, handles[_handleName].handle);
    }

    void DivisionGraph::DeleteHandle(std::string _name)
    {
        //ハンドルを検索して削除
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