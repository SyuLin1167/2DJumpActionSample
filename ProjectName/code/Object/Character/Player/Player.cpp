#include <DxLib.h>
#include <json.hpp>
#include <fstream>
#include "Player.h"
#include "KeyStatus/KeyStatus.h"
#include "Loading/LoadingContext.h"
#include "Jump/Jump.h"
#include "Graph/Graph.h"
#include "FileIO/ExeFilePath.h"

using json = nlohmann::json;

namespace object
{
    Player::Player()
        :id()
    {
        //json読み込みからの座標初期化
        task::LoadingContext::Get()->AddTask(task::DATA, [this]() {
            json j;
            auto fpath = file::GetExeDirectory() / "data/test.json";
            std::ifstream ifs(fpath.string());
            ifs >> j;
            pos.x = j["posX"].get<float>();
            pos.y = j["posY"].get<float>();
            ifs.close();
        });

        //プレイヤー画像読み込み
        assetMgr->Load<asset::Graph>("body", "player.png");
    }

    void Player::Init()
    {
        // ジャンプ機能追加
        auto jump = compMgr->AddComponent<component::Jump>(this, std::bind(input::KeyStatus::DecisionKeyState, keyType.A, ON_PRESS));

        // サイズ設定
        int imgW, imgH;
        GetGraphSize(assetMgr->Fetch<asset::Graph>()->GetHandle("body"), &imgW, &imgH);
        size = Vector2f(imgW, imgH);

        // 当たり判定追加
        col2d::ColliderDef colDef{};
        colDef.localPos = pos;
        colDef.isActive = true;
        colDef.shouldCCD = true;
        id = ObjCtx::ColMgr().CreateRectCollider(&colDef, size, MyObjectTag());

        // 衝突イベント追加
        col2d::ContactListener listener;
        listener.when = [&]() {return ObjCtx::ColMgr().GetCollider(id)->GetVelocity().y == 0 && velocity.y > 0; };
        listener.event = [&, jump]() {jump->CanJump(); };
        ObjCtx::ColMgr().AddEvent(id, col2d::MakeKey(col2d::TILE, ObjectTag::MAP), listener);
    }

    void Player::Update()
    {
        velocity.x = {};

        //移動処理
        if (input::KeyStatus::DecisionKeyState(keyType.LEFT, ON_PRESS | PRESSING))
        {
            velocity.x = -700 * deltaTime;
        }
        else if (input::KeyStatus::DecisionKeyState(keyType.RIGHT, ON_PRESS | PRESSING))
        {
            velocity.x = 700 * deltaTime;
        }
        ObjectContext::ColMgr().GetCollider(id)->SetVelocity(velocity);
    }

    void Player::LateUpdate()
    {
        pos = ObjCtx::ColMgr().GetCollider(id)->GetColliderDef()->localPos;
        velocity = ObjCtx::ColMgr().GetCollider(id)->GetVelocity();
    }

    void Player::Draw()
    {
        DrawGraph((int)pos.x, (int)pos.y, assetMgr->Fetch<asset::Graph>()->GetHandle("body"), true);
        DrawFormatString(1000, 10, GetColor(250, 250, 20), "move:←→\njump:Aキー");
    }
}
