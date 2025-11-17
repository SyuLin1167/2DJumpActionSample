module;
#include <json.hpp>

export module Object.PlayerData;

import MyLib.Math.Vector2;
import AppContext;

using json = nlohmann::json;
using namespace gameSystem;
using namespace math;

export namespace object
{
    export struct PlayerData
    {
        void Input(const json& data)
        {
            pos.x = data["posX"].get<float>();
            pos.y = data["posY"].get<float>();
            moveSpeed.x = data["moveSpeedX"].get<float>();
            moveSpeed.y = data["moveSpeedY"].get<float>();
        }

        Vector2f pos;
        Vector2f moveSpeed;
    };
}
