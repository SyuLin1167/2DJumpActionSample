export module UI.Button;

import <string>;
import <functional>;
import UI.UIBase;
import MyLib.Math.Vector2;
import MyLib.Shape.Rect;

using namespace math;

export namespace ui
{
    /// <summary>
    /// ボタン定義情報
    /// </summary>
    export struct ButtonDef
    {
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="_text">ボタンテキスト</param>
        /// <param name="_buttonRect">ボタンの形状</param>
        /// <param name="_color">ボタンの色</param>
        ButtonDef(const std::string& _text, const shape::Rect& _buttonRect,const uint32_t _color)
            :text(_text)
            , buttonRect(_buttonRect)
            , color(_color)
        {}

        std::string text;                   // ボタンテキスト
        shape::Rect buttonRect;             // ボタンの形状
        uint32_t color;                     // ボタンの色
        std::function<void()> onHover;      // ホバー時イベント
        std::function<void()> onClicked;    // クリック時イベント
        std::function<void()> onReleased;   // ボタンクリック後イベント
    };

    /// <summary>
    /// ボタンの機能を担当
    /// </summary>
    export class Button : public UIBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="def">ボタンの定義</param>
        Button(const ButtonDef* def);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Button();

        /// <summary>
        /// テキストの設定
        /// </summary>
        /// <param name="text">設定するテキスト</param>
        void SetText(const std::string& text)
        {
            m_def->text = text;
        }

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update() override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() override;

        // ホバー時処理
        void SetOnMouseHover(std::function<void()> hoverEvent)
        {
            m_def->onHover = std::move(hoverEvent);
        }

        // クリック時処理
        void SetOnClicked(std::function<void()> clickEvent)
        {
            m_def->onClicked = std::move(clickEvent);
        }

        // クリック後の処理
        void SetOnReleased(std::function<void()> releaseEvent)
        {
            m_def->onReleased = std::move(releaseEvent);
        }

    private:
        // クリック時処理
        void OnClick();

        void OnReleased();

        bool m_onClicked;
        std::unique_ptr<ButtonDef> m_def;
    };
}
