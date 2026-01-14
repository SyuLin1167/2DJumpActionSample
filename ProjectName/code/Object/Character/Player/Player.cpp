・ｿmodule;
#include <fstream>
#include <DxLib.h>
#include <json.hpp>

module Object.Player;

import MyLib.File.FileSystem;
import MyLib.KeyStatus;
import MyLib.Loading.LoadingContext;
import MyLib.Math.Vector2;
import GameSystem.Camera;
import Component.Jump;
import Component.MoveWithKey;
import Asset.Graph;

using json = nlohmann::json;
using namespace gameSystem;
using namespace math;

namespace object
{
    Player::Player()
        :id()
    {
        // 繝励Ξ繧､繝､繝ｼ蛻晄悄繝・・繧ｿ隱ｭ縺ｿ霎ｼ縺ｿ
        data = AppCtx::FileSystem().jsonIO.LoadAsync(AppCtx::FileSystem().GetDataDir() / "PlayerData");

        //繝励Ξ繧､繝､繝ｼ逕ｻ蜒剰ｪｭ縺ｿ霎ｼ縺ｿ
        AppCtx::AssetMgr().LoadAsync<asset::Graph>("body", "player.png");
    }

    Player::~Player()
    {
        AppCtx::AssetMgr().DeleteHandle<asset::Graph>("body");
    }

    void Player::Init()
    {
        // 繝励Ξ繧､繝､繝ｼ繝・・繧ｿ蜈･蜉・        PlayerData pData{};
        pData.Input(data.get());

        // 蛻晄悄菴咲ｽｮ險ｭ螳・        m_pos = pData.pos;

        // 繧ｫ繝｡繝ｩ霑ｽ蠕薙ち繝ｼ繧ｲ繝・ヨ險ｭ螳・        gameSystem::Camera::Instance().SetTarget(&m_pos);

        // 遘ｻ蜍墓ｩ溯・霑ｽ蜉
        auto move = m_compMgr->AddComponent<component::MoveWithKey>(this);
        move->SetHorizontal(keyType.LEFT, keyType.RIGHT, pData.moveSpeed.x);

        // 繧ｸ繝｣繝ｳ繝玲ｩ溯・霑ｽ蜉
        auto jump = m_compMgr->AddComponent<component::Jump>(this, pData.moveSpeed.y, std::bind(input::KeyStatus::CheckKey, keyType.SPACE, ON_PRESS));

        // 繧ｵ繧､繧ｺ險ｭ螳・        int imgW, imgH;
        GetGraphSize(AppCtx::AssetMgr().Fetch<asset::Graph>()->GetHandle("body"), &imgW, &imgH);

        // 蠖薙◆繧雁愛螳夊ｿｽ蜉
        col2d::ColliderDef colDef{};
        colDef.localPos = m_pos;
        colDef.isActive = true;
        colDef.shouldCCD = true;
        id = ObjCtx::ColMgr().CreateRectCollider(&colDef, Vector2f(imgW - 4, imgH), MyObjectTag());
        ObjCtx::ColMgr().AddMask(id, col2d::CIRCLE, ObjectTag::ENEMY);

        // 陦晉ｪ√う繝吶Φ繝郁ｿｽ蜉
        col2d::ContactListener listener;
        listener.when = [&]() {return ObjCtx::ColMgr().GetCollider(id)->GetVelocity().y == 0 && m_velocity.y > 0; };
        listener.event = [&, jump]() {jump->CanJump(); };
        ObjCtx::ColMgr().AddEvent(id, col2d::MakeKey(col2d::TILE, ObjectTag::MAP), listener);
    }

    void Player::Update()
    {
        // 騾溷ｺｦ蜿肴丐
        ObjectContext::ColMgr().GetCollider(id)->SetVelocity(m_velocity);
    }

    void Player::LateUpdate()
    {
        // 蠎ｧ讓呎峩譁ｰ
        m_pos = ObjCtx::ColMgr().GetCollider(id)->GetColliderDef()->localPos;

        // 騾溷ｺｦ譖ｴ譁ｰ
        m_velocity = ObjCtx::ColMgr().GetCollider(id)->GetVelocity();
    }

    void Player::Draw()
    {
        const Vector2f sp = gameSystem::Camera::Instance().WorldToScreen(m_pos);
        DrawGraph((int)sp.x, (int)sp.y, AppCtx::AssetMgr().Fetch<asset::Graph>()->GetHandle("body"), true);
    }
}
