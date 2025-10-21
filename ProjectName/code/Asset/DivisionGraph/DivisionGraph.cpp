module;
#include <DxLib.h>
#include <format>
#include <thread>

module Asset.DivisionGraph;

import MyLib.FileIO.ExeFilePath;
import MyLib.Loading.LoadingContext;

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
        // 情報取得の為、一時非同期モード解除
        SetUseASyncLoadFlag(false);

        // 画像読み込み
        auto fpath = file::GetExeDirectory() / std::format("assets/{}", graphName);
        int img = LoadGraph(fpath.string().c_str());

        // 読み込んだ画像から分割読み込みに必要な情報を保存
        int imgW, imgH;
        GetGraphSize(img, &imgW, &imgH);
        DeleteGraph(img);
        int col = imgW / m_divW;
        int row = imgH / m_divH;
        m_handles[handleName].total = col * row;
        m_handles[handleName].handle = new int[m_handles[handleName].total];

        // 非同期モード再開
        SetUseASyncLoadFlag(true);

        //取得した情報から画像分割読み込み
        LoadDivGraph(fpath.string().c_str(), m_handles[handleName].total, col, row, m_divW, m_divH, m_handles[handleName].handle);

        // 非同期読み込み中ならタスクに登録
        if (task::LoadingContext::Get())
        {
            task::LoadingContext::Get()->AddTask(task::GRAPH, [&, handleName]() {
                // ループ制御用の変数
                int total = m_handles[handleName].total;
                int done = false;
                
                // 非同期読み込み完了待ち
                while (true)
                {
                    // 分割分のハンドルの完了状況を見る
                    for (int i = 0; i < total; i++)
                    {
                        if (CheckHandleASyncLoad(m_handles[handleName].handle[i]))
                        {
                            done++;
                        }
                    }

                    // 全てのハンドルが読み込み完了していたら終了
                    if (done == total)
                    {
                        break;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            });
        }
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