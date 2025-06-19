#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "AssetBase/AssetBase.h"

/// <summary>
/// アセット関連
/// </summary>
namespace asset
{
    /// <summary>
    /// アセット全般を管理する
    /// </summary>
    class AssetManager final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        AssetManager() = default;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~AssetManager() = default;

        /// <summary>
        /// アセット読み込み
        /// </summary>
        /// <typeparam name="T">アセットの種類</typeparam>
        /// <typeparam name="...Args">引数</typeparam>
        /// <param name="_name">アセット名</param>
        /// <param name="_path">ファイルパス</param>
        /// <param name="..._args">引数群</param
        template<typename T, typename... Args>
        void Load(std::string _name, std::string _path, Args&&... _args)
        {
            if (registry.find(typeid(T)) == registry.end())
            {
                registry[typeid(T)] = std::make_unique<T>(std::forward<Args>(_args)...);
            }
            registry.at(typeid(T))->CreateHandle(_name, _path);
        }

        /// <summary>
        /// フェッチ
        /// </summary>
        /// <typeparam name="T">アセットの種類</typeparam>
        /// <returns>アセット</returns>
        template<typename T>
        T* Fetch()
        {
            auto it = registry.find(typeid(T));
            if (it != registry.end())
            {
                return static_cast<T*>(it->second.get());
            }
            return nullptr;
        }

        /// <summary>
        /// アセット削除
        /// </summary>
        /// <typeparam name="T">アセットの種類</typeparam>
        /// <param name="_name">アセット名</param>
        template<typename T>
        void Delete(std::string _name)
        {
            registry.at(typeid(T))->DeleteHandle(_name);
        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<AssetBase>> registry;   //アセット登録群
    };
}
