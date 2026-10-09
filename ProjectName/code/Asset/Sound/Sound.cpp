module;

#include <DxLib.h>

module Asset.Sound;

import <filesystem>;
import <thread>;
import MyLib.Loading.LoadingContext;
import AppContext;

using namespace gameSystem;

namespace asset
{
    Sound::~Sound()
    {
        for (auto& sound : m_sounds)
        {
            DeleteHandle(sound.second.soundDef.name);
        }
        m_sounds.clear();
    }

    void Sound::CreateHandle(std::string soundName, std::string fileName)
    {
        // 以前のハンドルを削除
        DeleteHandle(soundName);

        // SEでのファイル読み込み
        auto fpath = gameSystem::AppCtx::FileSystem().Resolve("assets://Sounds/SE/" + fileName);
        int handle;
        handle = LoadSoundMem(fpath.string().c_str());

        // SEでない場合、BGMでのファイル読み込み
        if (handle == -1)
        {
            fpath = gameSystem::AppCtx::FileSystem().Resolve("assets://Sounds/BGM/" + fileName);
            handle = LoadBGM(fpath.string().c_str());
        }
        m_sounds[soundName].handle = handle;
    }

    void Sound::CreateHandleAsync(std::string soundName, std::string fileName)
    {
        // 以前のハンドルを削除
        DeleteHandle(soundName);

        // SEでのファイル読み込み
        auto fpath = gameSystem::AppCtx::FileSystem().Resolve("assets://Sounds/SE/" + fileName);
        int handle;
        handle = LoadSoundMem(fpath.string().c_str());

        // SEでない場合、BGMでのファイル読み込み
        if (handle == -1)
        {
            fpath = gameSystem::AppCtx::FileSystem().Resolve("assets://Sounds/BGM/" + fileName);
            handle = LoadBGM(fpath.string().c_str());
        }

        // 非同期タスクを作成
        auto task = [this, handle, soundName]()
            {
                while (CheckHandleASyncLoad(handle))
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
                m_sounds[soundName].handle = handle;
            };

        // 非同期読み込み中ならタスクに登録
        if (task::LoadingContext::Get())
        {
            task::LoadingContext::Get()->AddTask(task::SOUND, task);
        }
        else
        {
            task();
        }
    }

    void Sound::AddSound(const SoundDef& soundDef, std::string fileName)
    {
        // サウンドファイル名がない場合、既にハンドルを持つデータとして追加
        if (fileName.empty())
        {
            m_sounds[soundDef.name].soundDef = soundDef;
            return;
        }

        // サウンドファイル名がある場合、データ追加とファイル読み込みを行う
        m_sounds.emplace(soundDef.name, soundDef);
        CreateHandleAsync(soundDef.name, fileName);
    }

    void Sound::DeleteHandle(std::string soundName)
    {
        // サウンドがなければログ追加
        if (m_sounds.find(soundName) == m_sounds.end())
        {
            ErrorLogFmtAdd("Sound is not found: %s",soundName.c_str());
            ErrorLogFmtAdd("サウンドが見つかりません: %s", soundName.c_str());
        }

        // サウンドハンドル削除
        DeleteSoundMem(m_sounds.at(soundName).handle);
    }

    void Sound::DeleteSound(const std::string& soundName)
    {
        // サウンドがなければログ追加
        if (m_sounds.find(soundName) == m_sounds.end())
        {
            ErrorLogFmtAdd("Sound is not found: %s", soundName.c_str());
            ErrorLogFmtAdd("サウンドが見つかりません: %s", soundName.c_str());
        }

        // サウンドの削除
        DeleteHandle(soundName);
        m_sounds.erase(soundName);
    }
}