export module ObjectContext;

import <optional>;

export import Collider;
export import Collider.ColliderManager;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    /// <summary>
    /// オブジェクトコンテキスト
    /// </summary>
    export struct ObjectContext final
    {
        /// <summary>
        /// アクティブ化
        /// </summary>
        static void Activate()
        {
            colMgr.emplace();
        }

        /// <summary>
        /// 非アクティブ化
        /// </summary>
        static void Deactivate()
        {
            colMgr.reset();
        }

        /// <summary>
        /// コライダー管理のインスタンスを返す
        /// </summary>
        /// <returns>コライダー管理のインスタンス</returns>
        static col2d::ColliderManager& ColMgr()
        {
            return *colMgr;
        }

    private:
        inline static std::optional<col2d::ColliderManager> colMgr{};   // コライダー管理のインスタンス
    };

    using ObjCtx = ObjectContext;
}