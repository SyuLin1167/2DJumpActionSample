module;
#include<DxLib.h>

module Object.Enemy;
import MyLib.Math.Vector2;

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
        DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 32, GetColor(255, 150, 0), TRUE);
    }
}
