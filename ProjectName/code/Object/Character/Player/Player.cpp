module;
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
        // プレイヤー初期データ読み込み
        data = AppCtx::FileSystem().jsonIO.LoadAsync(AppCtx::FileSystem().GetDataDir() / "PlayerData");

        //プレイヤー画像読み込み
        AppCtx::AssetMgr().LoadAsync<asset::Graph>("body", "player.png");
    }

    Player::~Player()
    {
        AppCtx::AssetMgr().DeleteHandle<asset::Graph>("body");
    }

    void Player::Init()
    {
        // プレイヤーデータ入力
        PlayerData pData{};
        pData.Input(data.get());

        // 初期位置設定
        m_pos = pData.pos;

        // カメラ追従ターゲット設定
        gameSystem::Camera::Instance().SetTarget(&m_pos);

        // 移動機能追加
        auto move = m_compMgr->AddComponent<component::MoveWithKey>(this);
        move->SetHorizontal(keyType.LEFT, keyType.RIGHT, pData.moveSpeed.x);

        // ジャンプ機能追加
        auto jump = m_compMgr->AddComponent<component::Jump>(this, pData.moveSpeed.y, std::bind(input::KeyStatus::CheckKey, keyType.SPACE, ON_PRESS));

        // サイズ設定
        int imgW, imgH;
        GetGraphSize(AppCtx::AssetMgr().Fetch<asset::Graph>()->GetHandle("body"), &imgW, &imgH);

        // 当たり判定追加
        col2d::ColliderDef colDef{};
        colDef.localPos = m_pos;
        colDef.isActive = true;
        colDef.shouldCCD = true;
        id = ObjCtx::ColMgr().CreateRectCollider(&colDef, Vector2f(imgW - 4, imgH), MyObjectTag());
        ObjCtx::ColMgr().AddMask(id, col2d::CIRCLE, ObjectTag::ENEMY);

        // 衝突イベント追加
        col2d::ContactListener listener;
        listener.when = [&]() {return ObjCtx::ColMgr().GetCollider(id)->GetVelocity().y == 0 && m_velocity.y > 0; };
        listener.event = [&, jump]() {jump->CanJump(); };
        ObjCtx::ColMgr().AddEvent(id, col2d::MakeKey(col2d::TILE, ObjectTag::MAP), listener);
    }

    void Player::Update()
    {
        // 速度反映
        ObjectContext::ColMgr().GetCollider(id)->SetVelocity(m_velocity);
    }

    void Player::LateUpdate()
    {
        // 座標更新
        m_pos = ObjCtx::ColMgr().GetCollider(id)->GetColliderDef()->localPos;

        // 速度更新
        m_velocity = ObjCtx::ColMgr().GetCollider(id)->GetVelocity();
    }

    void Player::Draw()
    {
        const Vector2f sp = gameSystem::Camera::Instance().WorldToScreen(m_pos);
        DrawGraph((int)sp.x, (int)sp.y, AppCtx::AssetMgr().Fetch<asset::Graph>()->GetHandle("body"), true);

        DrawFormatString(1000, 10, GetColor(250, 250, 20), "move:←→\njump:Aキー");

        // デバッグ表示: ワールド座標 / スクリーン座標 / カメラオフセット / 速度
        const auto camOffset = gameSystem::Camera::Instance().GetOffset();
        DrawFormatString(10, 10, GetColor(250, 250, 20),
            "World:(%.1f,%.1f)\nScreen:(%.1f,%.1f)\nCamOff:(%.1f,%.1f)\nVel:(%.2f,%.2f)",
            m_pos.x, m_pos.y, sp.x, sp.y, camOffset.x, camOffset.y, m_velocity.x, m_velocity.y);

    }
}
