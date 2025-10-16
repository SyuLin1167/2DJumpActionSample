module;
#include <DxLib.h>
#include <format>

module Asset.DivisionGraph;

import MyLib.FileIO.ExeFilePath;

namespace asset
{
    DivisionGraph::DivisionGraph(int divW, int divH)
        : m_divW(divW)
        , m_divH(divH)
        , m_handles()
    {
        //処理なし
    }

    DivisionGraph::~DivisionGraph()
    {
        //確保した画像の解放
        for (auto& info : m_handles)
        {
            for (int i = 0; i < info.second.total; i++)
            {
                DeleteGraph(info.second.handle[i]);
            }
        }
    }

    void DivisionGraph::CreateHandle(std::string handleName, std::string graphName)
    {
        //画像の情報を収集
        auto fpath = file::GetExeDirectory() / std::format("assets/{}", graphName);
        int img = LoadGraph(fpath.string().c_str());
        int imgW, imgH;
        GetGraphSize(img, &imgW, &imgH);
        DeleteGraph(img);
        int col = imgW / m_divW;
        int row = imgH / m_divH;
        m_handles[handleName].total = col * row;
        m_handles[handleName].handle = new int[m_handles[handleName].total];

        //取得した情報から画像分割読み込み
        LoadDivGraph(fpath.string().c_str(), m_handles[handleName].total, col, row, m_divW, m_divH, m_handles[handleName].handle);
    }

    void DivisionGraph::DeleteHandle(std::string name)
    {
        //ハンドルを検索して削除
        auto it = m_handles.find(name);
        if (it == m_handles.end())
        {
            return;
        }

        for (int i = 0; i < it->second.total; ++i)
        {
            DeleteGraph(it->second.handle[i]);
        }

        delete[] it->second.handle;
        m_handles.erase(it);
    }
}