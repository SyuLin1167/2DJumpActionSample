# GameSystem.Camera

2Dカメラ / インスタンス生成

所属：[game-systemのAPI解説](../game-system.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/code/GameSystem/Camera/Camera.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/code/GameSystem/Camera/Camera.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module GameSystem.Camera;

import MyLib.Math.Vector2;
import GameSystem.Window;
import Object.GameObject;

using namespace math;

export namespace gameSystem
{
    /// <summary>
    /// 2Dカメラ
    /// </summary>
    export class Camera final
    {
    public:
        /// <summary>
        /// インスタンス生成
        /// </summary>
        /// <returns>カメラインスタンス</returns>
        static Camera& Instance()
        {
            static Camera inst;
            return inst;
        }

        /// <summary>
        /// 追尾ターゲット設定
        /// </summary>
        /// <param name="target">追尾対象のゲームオブジェクト</param>
        void SetTarget(Vector2f* target)
        {
            m_target = target;
        }

        /// <summary>
        /// 追尾ターゲット解除(自分が登録したターゲットの場合のみ)
        /// </summary>
        /// <param name="target">解除するターゲット</param>
        void ClearTarget(const Vector2f* target)
        {
            if (m_target == target)
            {
                m_target = nullptr;
            }
        }

        /// <summary>
        /// ワールド全体サイズ設定
        /// </summary>
        /// <param name="worldSize">ワールドサイズ</param>
        void SetWorldSize(const Vector2f& worldSize= Vector2f(1920.0f, 1080.0f))
        {
            m_worldSize = worldSize;
            ClampPosition();
        }

        /// <summary>
        /// 更新
        /// </summary>
        void Update();

        /// <summary>
        /// 現在のオフセット
        /// </summary>
        Vector2f GetOffset() const
        {
            return m_pos;
        }

        /// <summary>
        /// ワールド→スクリーン座標変換
        /// </summary>
        /// <param name="worldPos">ワールド座標</param>
        /// <returns>スクリーン座標</returns>
        Vector2f WorldToScreen(const Vector2f& worldPos) const
        {
            return worldPos - m_pos;
        }

        /// <summary>
        /// ワールド→スクリーン座標変換
        /// </summary>
        /// <param name="x">ワールド座標X</param>
        /// <param name="y">ワールド座標Y</param>
        /// <returns>スクリーン座標</returns>
        Vector2f WorldToScreen(float x, float y) const
        {
            return Vector2f(x, y) - m_pos;
        }

    private:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Camera();

        /// <summary>
        /// 位置クランプ
        /// </summary>
        void ClampPosition();

        Vector2f* m_target;           // 追尾ターゲット
        Vector2f m_pos;              // カメラ位置（オフセット）
        Vector2f m_worldSize;        // ワールド全体サイズ
        float m_followStrength;      // 追尾強度
    };
}
```
