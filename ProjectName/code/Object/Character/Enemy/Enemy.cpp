module;
#include<DxLib.h>

module Object.Enemy;
import MyLib.Math.Vector2;
import GameSystem.Camera;

using namespace math;

namespace object
{
    Enemy::Enemy()
        :id()
    {
        m_pos = {420,230};
    }

    Enemy::~Enemy() = default;
    
    void Enemy::Init()
    {
        col2d::ColliderDef def{};
        def.localPos = m_pos;
        def.isActive = true;
        id = ObjCtx::ColMgr().CreateCircleCollider(&def, 32.0f, MyObjectTag());
    }

    void Enemy::Update() {}
    void Enemy::LateUpdate() {}
    void Enemy::Draw()
    {
        const auto sp = gameSystem::Camera::Instance().WorldToScreen(m_pos);
        DrawCircle(static_cast<int>(sp.x), static_cast<int>(sp.y), 32, GetColor(255, 150, 0), TRUE);
    }
}
