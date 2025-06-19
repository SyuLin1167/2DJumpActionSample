#include <DxLib.h>
#include "Title.h"
#include "KeyStatus/KeyStatus.h"
#include "FileIO/ExeFilePath.h"
#include "Loading/LoadingContext.h"
#include "LoadingScene/LoadingScene.h"
#include "Play/Play.h"

namespace scene
{
    Title::Title()
    {
        //シェーダー読み込み
        auto VSfpath = file::GetExeDirectory() / "shader/VertexShader.vso";
        vs = LoadVertexShader(VSfpath.string().c_str());
        auto PSfpath = file::GetExeDirectory() / "shader/PixelShader.pso";
        ps = LoadPixelShader(PSfpath.string().c_str());

        // 頂点データの準備
        Vert[0].pos = VGet(0.0f, 0.0f, 0.0f);
        Vert[1].pos = VGet(128.0f, 0.0f, 0.0f);
        Vert[2].pos = VGet(0.0f, 128.0f, 0.0f);
        Vert[3].pos = VGet(128.0f, 128.0f, 0.0f);

        Vert[0].dif = GetColorU8(255, 0, 255, 100);
        Vert[1].dif = GetColorU8(255, 255, 0, 255);
        Vert[2].dif = GetColorU8(255, 0, 0, 100);
        Vert[3].dif = GetColorU8(255, 255, 255, 255);

        Vert[0].spc = GetColorU8(0, 255, 0, 0);
        Vert[1].spc = GetColorU8(0, 255, 0, 0);
        Vert[2].spc = GetColorU8(0, 255, 0, 0);
        Vert[3].spc = GetColorU8(0, 255, 0, 0);

        Vert[0].rhw = Vert[1].rhw = Vert[2].rhw = Vert[3].rhw = 1.0f;
        Vert[0].u = Vert[1].u = Vert[2].u = Vert[3].u = 0.0f;
        Vert[0].v = Vert[1].v = Vert[2].v = Vert[3].v = 0.0f;
        Vert[0].su = Vert[1].su = Vert[2].su = Vert[3].su = 0.0f;
        Vert[0].sv = Vert[1].sv = Vert[2].sv = Vert[3].sv = 0.0f;

        Vert[4] = Vert[2];
        Vert[5] = Vert[1];
    }

    Title::~Title()
    {
        DeleteShader(vs);
        DeleteShader(ps);
    }

    std::shared_ptr<SceneBase> Title::Update()
    {
        //Eキーが押されていたらシーン移動
        if (input::KeyStatus::DecisionKeyState(keyType.E, ON_PRESS))
        {
            return std::make_shared<LoadingScene>(LoadPolicy::PROGRESS, CreateNextScene<Play>, shared_from_this());
        }

        int x, y;
        GetMousePoint(&x, &y);
        Vert[0].pos = VGet(0.0f + x, 0.0f + y, 0.0f);
        Vert[1].pos = VGet(128.0f + x, 0.0f + y, 0.0f);
        Vert[2].pos = VGet(0.0f + x, 128.0f + y, 0.0f);
        Vert[3].pos = VGet(128.0f + x, 128.0f + y, 0.0f);

        for (int v = 0 ; v < 6; v++)
        {
            Vert[v].dif = GetColorU8(static_cast<int>(Vert[v].pos.x), static_cast<int>(Vert[v].pos.y), static_cast<int>(Vert[v].pos.x + Vert[v].pos.y) / 2, 255);
        }

        Vert[4] = Vert[2];
        Vert[5] = Vert[1];

        return shared_from_this();
    }

    void Title::Draw()
    {
        SetUseVertexShader(vs);
        SetUsePixelShader(ps);

        DrawPolygon2DToShader(Vert, 2);
    }

    void Title::DrawLoading()
    {
        float progress = task::LoadingContext::Get()->NowProgress() * 100.0f;
        DrawFormatString(120, 120, GetColor(250, 100, 150), "ローディング進捗度：%.2f％", progress);
    }
}
