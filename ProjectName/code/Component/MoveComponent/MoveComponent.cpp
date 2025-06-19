#include "MoveComponent.h"
#include "GameObject/GameObject.h"

namespace comp
{
    MoveComponent::MoveComponent(object::GameObject* owner)
        :Component(owner)
    {
        dataX = new MoveData(300, 0, 1920);
        dataY = new MoveData(300, 0, 1080);
    }

    MoveComponent::~MoveComponent()
    {
        delete dataX;
        delete dataY;
    }

    void MoveComponent::Update(const float& deltaTime)
    {
        //座標移動
        owner->AccessPos().Assign(PropVector2<float>::X, AutoMoveToRange(owner->AccessPos().NowX(), dataX, deltaTime));
        owner->AccessPos().Assign(PropVector2<float>::Y, AutoMoveToRange(owner->AccessPos().NowY(), dataY, deltaTime));
    }

    float MoveComponent::AutoMoveToRange(const float pos, MoveData* moveData, const float& deltaTime)
    {
        //範囲内を移動させる
        if (pos < moveData->min)
        {
            moveData->speed = abs(moveData->speed);
        }
        else if (pos > moveData->max)
        {
            moveData->speed = -moveData->speed;
        }

        return pos + moveData->speed * deltaTime;
    }

    MoveComponent::MoveData::MoveData(float speed, int min, int max)
    {
        this->speed = speed;
        this->min = min;
        this->max = max;
    }
}
