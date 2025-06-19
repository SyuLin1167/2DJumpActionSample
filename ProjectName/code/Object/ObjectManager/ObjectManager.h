#pragma once
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

/// <summary>
/// オブジェクト関連
/// </summary>
namespace object
{
    class GameObject;

    /// <summary>
    /// オブジェクトを管理する
    /// </summary>
    class ObjectManager final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        ObjectManager();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~ObjectManager() = default;

        /// <summary>
        /// オブジェクト追加
        /// </summary>
        /// <param name="object">追加するオブジェクト</param>
        void AddObject(GameObject* object);

        /// <summary>
        /// オブジェクト除去
        /// </summary>
        /// <param name="object">除去するオブジェクト</param>
        void RemoveObject(GameObject* object);

        /// <summary>
        /// 更新処理前の初期化
        /// </summary>
        void InitBeforeUpdate();

        /// <summary>
        /// オブジェクト更新
        /// </summary>
        void Update();

        /// <summary>
        /// オブジェクト取得
        /// </summary>
        /// <param name="tag">タグ</param>
        /// <returns>タグに該当するオブジェクト群</returns>
        std::vector<std::shared_ptr<GameObject>> GetObjForTag(uint32_t tag);

        /// <summary>
        /// オブジェクト描画
        /// </summary>
        void Draw();

    private:
        std::unordered_map<uint32_t, std::vector<std::shared_ptr<GameObject>>> objects;     //オブジェクト配列
        std::vector<GameObject*> pendingObjects;    //一時保存オブジェクト配列
        bool isUpdate;                              //更新状況
    };
}
