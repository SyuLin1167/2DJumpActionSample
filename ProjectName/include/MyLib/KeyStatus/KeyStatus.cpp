#include <DxLib.h>
#include "KeyStatus.h"

namespace input
{
    std::unique_ptr<KeyStatus> KeyStatus::keyStatus = nullptr;

    void KeyStatus::InitInstance()
    {
        //自身の中身が空だったらインスタンス生成
        if (!keyStatus) {
            keyStatus.reset(new KeyStatus);
        }
    }

    KeyStatus::KeyStatus()
    {
        //使用するキーの情報を一通り作成
        for (auto& keyName : KEYS) {
            keyData.emplace(keyName, ON_RELEASE);
        }
    }

    bool KeyStatus::DecisionKeyState(const int key, const int state)
    {
        //押下中判定結果を返す
        if (keyStatus->keyData[key] & state) {
            return true;
        }
        return false;
    }

    void KeyStatus::UpdateKeyState()
    {
        //キーのステータスを一通り切り替える
        for (auto& key : keyStatus->keyData) {
            if (CheckHitKey(key.first)) {
                if (key.second & (ON_RELEASE | RELEASING)) {
                    key.second = ON_PRESS;
                    continue;
                }
                key.second = PRESSING;
            }
            else {
                if (key.second & (ON_PRESS | PRESSING)) {
                    key.second = ON_RELEASE;
                    continue;
                }
                key.second = RELEASING;
            }
        }
    }
}