・ｿmodule;
#include <DxLib.h>

module MyLib.KeyStatus;

namespace input
{
    KeyStatus::KeyStatus()
    {
        //菴ｿ逕ｨ縺吶ｋ繧ｭ繝ｼ縺ｮ諠・ｱ繧剃ｸ騾壹ｊ菴懈・
        for (auto& keyName : KEYS)
        {
            keyData.emplace(keyName, ON_RELEASE);
        }
    }

    void KeyStatus::UpdateKeyStateImpl()
    {
        //繧ｭ繝ｼ縺ｮ繧ｹ繝・・繧ｿ繧ｹ繧剃ｸ騾壹ｊ蛻・ｊ譖ｿ縺医ｋ
        for (auto& key : keyData)
        {
            // 謚ｼ荳倶ｸｭ縺九←縺・°縺ｧ蝣ｴ蜷亥・縺・            if (CheckHitKey(key.first))
            {
                // 謚ｼ荳倶ｸｭ縺ｮ蝣ｴ蜷・                if (key.second & (ON_RELEASE | RELEASING))
                {
                    key.second = ON_PRESS;
                    continue;
                }
                key.second = PRESSING;
            }
            else
            {
                // 謚ｼ荳九＆繧後※縺・↑縺・ｴ蜷・                if (key.second & (ON_PRESS | PRESSING))
                {
                    key.second = ON_RELEASE;
                    continue;
                }
                key.second = RELEASING;
            }
        }
    }
}