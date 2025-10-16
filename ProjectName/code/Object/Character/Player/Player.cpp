module;
#include <fstream>
#include <DxLib.h>
#include <json.hpp>

module Object.Player;

import MyLib.FileIO.ExeFilePath;
import MyLib.KeyStatus;
import MyLib.Loading.LoadingContext;
import MyLib.Math.Vector2;
import Component.Jump;
import Asset.Graph;

using json = nlohmann::json;
using namespace math;

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
            m_pos.x = j["posX"].get<float>();
            m_pos.y = j["posY"].get<float>();
            ifs.close();
        });

        //プレイヤー画像読み込み
        m_assetMgr->Load<asset::Graph>("body", "player.png");
    }

    void Player::Init()
    {
        // ジャンプ機能追加
        auto jump = m_compMgr->AddComponent<component::Jump>(this, std::bind(input::KeyStatus::DecisionKeyState, keyType.A, ON_PRESS));

        // サイズ設定
        int imgW, imgH;
        GetGraphSize(m_assetMgr->Fetch<asset::Graph>()->GetHandle("body"), &imgW, &imgH);
        m_size = Vector2f((float)imgW, (float)imgH);

        // 当たり判定追加
        col2d::ColliderDef colDef{};
        colDef.localPos = m_pos;
        colDef.isActive = true;
        colDef.shouldCCD = true;
        id = ObjCtx::ColMgr().CreateRectCollider(&colDef, m_size, MyObjectTag());

        // 衝突イベント追加
        col2d::ContactListener listener;
        listener.when = [&]() {return ObjCtx::ColMgr().GetCollider(id)->GetVelocity().y == 0 && m_velocity.y > 0; };
        listener.event = [&, jump]() {jump->CanJump(); };
        ObjCtx::ColMgr().AddEvent(id, col2d::MakeKey(col2d::TILE, ObjectTag::MAP), listener);
    }

    void Player::Update()
    {
        m_velocity.x = {};

        //移動処理
        if (input::KeyStatus::DecisionKeyState(keyType.LEFT, ON_PRESS | PRESSING))
        {
            m_velocity.x = -700 * m_deltaTime;
        }
        else if (input::KeyStatus::DecisionKeyState(keyType.RIGHT, ON_PRESS | PRESSING))
        {
            m_velocity.x = 700 * m_deltaTime;
        }
        ObjectContext::ColMgr().GetCollider(id)->SetVelocity(m_velocity);
    }

    void Player::LateUpdate()
    {
        m_pos = ObjCtx::ColMgr().GetCollider(id)->GetColliderDef()->localPos;
        m_velocity = ObjCtx::ColMgr().GetCollider(id)->GetVelocity();
    }

    void Player::Draw()
    {
        DrawGraph((int)m_pos.x, (int)m_pos.y, m_assetMgr->Fetch<asset::Graph>()->GetHandle("body"), true);
        DrawFormatString(1000, 10, GetColor(250, 250, 20), "move:←→\njump:Aキー");
    }
}
