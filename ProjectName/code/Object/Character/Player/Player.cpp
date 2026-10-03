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
import Component.Animator;
import Asset.Animation;

using json = nlohmann::json;
using namespace gameSystem;
using namespace math;

namespace object
{
    Player::Player()
        :id()
    {
        // プレイヤー初期データ読み込み
        json data = AppCtx::FileSystem().jsonIO.Load(AppCtx::FileSystem().GetDataDir() / "PlayerData");
        pData.Input(data);

        //プレイヤー画像読み込み
        AppCtx::AssetMgr().Fetch<asset::Animation>()->CreateHandleAsync(AssetName::IDLE, "player.png", pData.size.x, pData.size.y);
    }

    Player::~Player()
    {
    }

    void Player::Init()
    {
        // 初期位置設定
        m_pos = pData.pos;

        // カメラ追従ターゲット設定
        gameSystem::Camera::Instance().SetTarget(&m_pos);

        // 移動機能追加
        auto move = m_compMgr->AddComponent<component::MoveWithKey>(this);
        move->SetHorizontal(keyType.LEFT, keyType.RIGHT, pData.moveSpeed.x);

        // ジャンプ機能追加
        auto jump = m_compMgr->AddComponent<component::Jump>(this, pData.moveSpeed.y, std::bind(input::KeyStatus::CheckKey, keyType.SPACE, ON_PRESS));

        // 当たり判定追加
        col2d::ColliderDef colDef{};
        colDef.localPos = m_pos;
        colDef.isActive = true;
        colDef.shouldCCD = true;
        id = ObjCtx::ColMgr().CreateRectCollider(&colDef, pData.size, MyObjectTag());
        ObjCtx::ColMgr().AddMask(id, col2d::CIRCLE, ObjectTag::ENEMY);

        // 衝突イベント追加
        col2d::ContactListener listener;
        listener.when = [&]() {return ObjCtx::ColMgr().GetCollider(id)->GetVelocity().y == 0 && m_velocity.y > 0; };
        listener.event = [&, jump]() { m_velocity.y = 0; jump->CanJump();};
        ObjCtx::ColMgr().AddEvent(id, col2d::MakeKey(col2d::TILE, ObjectTag::MAP), listener);

        // アニメーション追加
        auto anim = m_compMgr->AddComponent<component::Animator>(this);
        asset::AnimationDef animDef{};
        animDef.name = AssetName::IDLE;
        animDef.type = asset::AnimType::LOOP;
        animDef.animationSpeed = 4;
        animDef.endFrame = 4;
        animDef.size = pData.size;
        AppCtx::AssetMgr().Fetch<asset::Animation>()->AddAnim(animDef);
        m_compMgr->GetComponent<component::Animator>()->PlayAnim(AssetName::IDLE);
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
        // 処理なし
    }
}
