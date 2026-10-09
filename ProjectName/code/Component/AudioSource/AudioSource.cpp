module;

#include <DxLib.h>

module Component.AudioSource;

import AppContext;
import Asset.Sound;
import Component;
import Asset.SoundDef;

using namespace gameSystem;
using namespace asset;

namespace component
{
    AudioSource::AudioSource(object::GameObject* owner)
        : ComponentBase(owner)
        , m_states()
    {
        // 処理なし
    }

    AudioSource::~AudioSource()
    {
        m_states.clear();
    }

    void AudioSource::PlaySound(const std::string& soundName)
    {
        // サウンドがない場合は再生しない
        if (m_states.find(soundName) == m_states.end())
        {
            return;
        }

        // サウンドハンドルがない場合は再生しない
        auto sound = AppCtx::AssetMgr().Fetch<Sound>()->GetSound(soundName);
        if (sound.handle == -1)
        {
            return;
        }

        // 音量設定
        ChangeVolumeSoundMem(sound.soundDef.volume, sound.handle);

        // SE(単発)の場合は複製ハンドルを再生
        if (sound.soundDef.soundType = SOUNDTYPE_SE_ONCE)
        {
            int handle = DuplicateSoundMem(sound.handle);
            PlaySoundMem(handle, sound.soundDef.soundType);

            // 再生終了後に自動削除
            SetPlayFinishDeleteSoundMem(TRUE, handle);
            return;
        }

        // サウンド再生
        if (m_states[soundName] == SoundState::PAUSE)
        {
            PlaySoundMem(sound.handle, sound.soundDef.soundType, false);
        }
        else if(m_states[soundName] == SoundState::STOP)
        {
            PlaySoundMem(sound.handle, sound.soundDef.soundType);
        }
        m_states[soundName] = SoundState::PLAY;
    }

    void AudioSource::PauseSound(const std::string& soundName)
    {
        // サウンドがない場合は一時停止しない
        if (m_states.find(soundName) == m_states.end())
        {
            return;
        }

        // サウンドハンドルがない場合は一時停止しない
        auto sound = AppCtx::AssetMgr().Fetch<Sound>()->GetSound(soundName);
        if (sound.handle == -1)
        {
            return;
        }

        // サウンド一時停止
        StopSoundMem(sound.handle);
        auto& playState = m_states.at(soundName);
        playState.soundState = SoundState::PAUSE;
    }

    void AudioSource::StopSound(const std::string& soundName)
    {
        // サウンドがない場合は停止しない
        if (m_states.find(soundName) == m_states.end())
        {
            return;
        }

        // サウンドハンドルがない場合は停止しない
        auto sound = AppCtx::AssetMgr().Fetch<Sound>()->GetSound(soundName);
        if (sound.handle == -1)
        {
            return;
        }

        // サウンド停止
        StopSoundMem(sound.handle);
        auto& playState = m_states.at(soundName);
        playState.soundState = SoundState::STOP;
    }
}

