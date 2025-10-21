module;
#include <DxLib.h>

module Scene.LoadingScene;
import GameSystem.FrameRate;
import MyLib.Loading;
import MyLib.Loading.LoadingContext;

namespace scene
{
    LoadingScene::LoadingScene(int8_t policy, std::function<std::shared_ptr<SceneBase>()> nextScene, std::shared_ptr<SceneBase> holdScene)
        : m_policy(policy)
        , m_loadScene(nextScene)
        , m_holdScene(std::move(holdScene))
        , m_coroutine()
    {
        // ローディング開始
        SetUseASyncLoadFlag(true);
        task::LoadingContext::Set(std::make_unique<task::Loading>().release());
        task::LoadingContext::Get()->StartLoading();
        task::LoadingContext::Get()->WatchProgress();

        // ポリシー別処理
        if (m_policy & (LoadPolicy::COROUTINE | LoadPolicy::PROGRESS))
        {
            m_coroutine = std::move(LoadCoroutine());
        }
        else if (m_policy & LoadPolicy::DONE)
        {
            m_nextScene = m_loadScene();
        }
    }

    LoadingScene::~LoadingScene()
    {
        SetUseASyncLoadFlag(false);
        task::LoadingContext::Release();
    }

    Coroutine LoadingScene::LoadCoroutine()
    {
        // 次シーンのローディング処理
        m_nextScene = m_loadScene();

        // 読み込み完了まで待機
        co_yield WaitUntil{ [this] { return !task::LoadingContext::Get()->IsLoading(); } };

        // 100％表示用
        co_yield WaitForSeconds{ 0.5f };

        // 読み込み完了
        co_return;
    }

    std::shared_ptr<SceneBase> LoadingScene::Update()
    {
        // ポリシーに基づいた行進処理
        if (m_policy & (LoadPolicy::COROUTINE | LoadPolicy::PROGRESS))
        {
            // コルーチン実行
            if (m_coroutine.handle)
            {
                // 待機処理
                auto yieldType = m_coroutine.get_yield_type();
                if (std::holds_alternative<WaitForSeconds>(yieldType))
                {
                    // 指定時間待機
                    auto& wait = std::get<WaitForSeconds>(yieldType);
                    static float elapsed = 0.0f;
                    elapsed += gameSystem::FrameRate::Instance().GetDeltaTime();
                    if (elapsed < wait.seconds)
                    {
                        return shared_from_this();
                    }
                }
                else if (std::holds_alternative<WaitUntil>(yieldType))
                {
                    // 指定条件完了確認
                    auto& wait = std::get<WaitUntil>(yieldType);
                    if (!wait.pred())
                    {
                        return shared_from_this();
                    }
                }

                // コルーチン再開
                m_coroutine.resume();

                // コルーチン完了確認
                if (m_coroutine.handle.done())
                {
                    return m_nextScene;
                }
            }
        }
        else if (m_policy & LoadPolicy::DONE)
        {
            // 読み込み完了確認
            if (!task::LoadingContext::Get()->IsLoading())
            {
                return m_nextScene;
            }
        }

        // 保持しているシーンの更新
        return shared_from_this();
    }

    void LoadingScene::Draw()
    {
        if (m_holdScene)
        {
            if (m_policy & LoadPolicy::PROGRESS)
            {
                m_holdScene->Draw();
            }

            m_holdScene->DrawLoading();
        }
    }
}
