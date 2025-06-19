#include "LoadingScene.h"
#include "Loading/Loading.h"
#include "Loading/LoadingContext.h"

namespace scene
{
    LoadingScene::LoadingScene(int8_t _policy, std::function<std::shared_ptr<SceneBase>()> _nextScene, std::shared_ptr<SceneBase> _holdScene)
        : policy(_policy)
        , loadScene(_nextScene)
        , holdScene(std::move(_holdScene))
        , coroutine()
    {
        //ローディング開始
        loading = std::make_unique<task::Loading>();
        task::LoadingContext::Set(loading.get());
        loading->StartLoading();

        //ポリシー別処理
        if (policy & (LoadPolicy::COROUTINE | LoadPolicy::PROGRESS))
        {
            coroutine = std::move(LoadCoroutine());
        }
        else if (policy & LoadPolicy::DONE)
        {
            nextScene = loadScene();
        }
    }

    Coroutine LoadingScene::LoadCoroutine()
    {
        //次シーンのローディング処理
        nextScene = loadScene();
        while (loading->IsLoading())
        {
            co_yield WaitForSeconds{ 0.01f };
        }

        //100％表示用
        float timer = 0.0f;
        while (timer < 0.8f)
        {
            co_yield WaitForSeconds{ 0.01f };
            timer += 0.01f;
        }

        co_return;
    }

    std::shared_ptr<SceneBase> LoadingScene::Update()
    {
        //ポリシーに基づいた行進処理
        if (policy & (LoadPolicy::COROUTINE | LoadPolicy::PROGRESS))
        {
            if (coroutine.handle)
            {
                coroutine.resume();
                if (coroutine.handle.done())
                {
                    return nextScene;
                }
            }
        }
        else if (policy & LoadPolicy::DONE)
        {
            if (!loading->IsLoading())
            {
                return nextScene;
            }
        }

        return shared_from_this();
    }

    void LoadingScene::Draw()
    {
        if (policy & LoadPolicy::PROGRESS)
        {
            holdScene->Draw();
        }

        holdScene->DrawLoading();
    }
}
