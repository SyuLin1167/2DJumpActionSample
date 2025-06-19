#pragma once
#include "Component.h"

namespace comp
{
    /// <summary>
    /// 移動用コンポーネント
    /// </summary>
    class MoveComponent final : public Component
    {
    private:
        /// <summary>
        /// 移動に必要な情報
        /// </summary>
        struct MoveData
        {
            /// <summary>
            /// コンストラクタ
            /// </summary>
            /// <param name="speed">速度</param>
            /// <param name="min">最小値</param>
            /// <param name="max">最大値</param>
            MoveData(float speed, int min, int max);

            float speed;    //速度
            int min;        //最小値
            int max;        //最大値
        };

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="owner">所有者</param>
        /// <param name="order">更新の優先順位</param>
        MoveComponent(object::GameObject* owner);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~MoveComponent();

        /// <summary>
        /// 更新
        /// </summary>
        /// <param name="deltaTime">デルタタイム</param>
        void Update(const float& deltaTime) override;

        /// <summary>
        /// 自動範囲内移動
        /// </summary>
        /// <param name="pos">座標</param>
        /// <param name="moveData">移動に必要な情報</param>
        /// <param name="deltaTime"></param>
        /// <returns></returns>
        float AutoMoveToRange(const float pos, MoveData* moveData, const float& deltaTime);

    private:
        MoveData* dataX;    //X軸用の情報
        MoveData* dataY;    //Y軸用の情報
    };
}
