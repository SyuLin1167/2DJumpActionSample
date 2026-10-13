# MyLib.ClickStatus

���͊֘A�i�N���b�N�j / �N���b�N���̊Ǘ�

所属：[mylibのAPI解説](../mylib.md) · [全モジュール索引](../modules.md)

## 読み方

このページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。

元ファイル：[ProjectName/include/MyLib/ClickStatus/ClickStatus.ixx](https://github.com/SyuLin1167/2DGameSample/blob/08f9fa53fa5e9043d46aeede8e7aab7bab519892/ProjectName/include/MyLib/ClickStatus/ClickStatus.ixx)。確認基準：`08f9fa53`。

## インターフェースとインライン実装

```cpp
export module MyLib.ClickStatus;

import <unordered_map>;

export constexpr int8_t CLICK_ON_RELEASE = 0x0001;   // �����͎�
export constexpr int8_t CLICK_RELEASING  = 0x0002;   // �����͒�
export constexpr int8_t CLICK_ON_PRESS   = 0x0004;   // ���͎�
export constexpr int8_t CLICK_PRESSING   = 0x0008;   // ���͒�

/// <summary>
/// ���͊֘A�i�N���b�N�j
/// </summary>
export namespace input
{
    /// <summary>
    /// �N���b�N���̊Ǘ�
    /// </summary>
    export class ClickStatus final
    {
    public:
        /// <summary>
        /// �C���X�^���X��Ԃ�
        /// </summary>
        /// <returns>���g�̃C���X�^���X</returns>
        static ClickStatus& Instance()
        {
            static ClickStatus instance;
            return instance;
        }

        /// <summary>
        /// �N���b�N���X�V
        /// </summary>
        inline void UpdateClickState()
        {
            Instance().UpdateClickStateImpl();
        }

        /// <summary>
        /// �N���b�N��񔻒�
        /// </summary>
        /// <param name="button">�Ώۃ{�^���i��: ��=0, �E=1 �Ȃǁj</param>
        /// <param name="state">�ΏۃX�e�[�^�X</param>
        /// <returns>��v:true | �s��v:false</returns>
        static bool CheckClick(const int& button, const int& state)
        {
            return Instance().CheckClickImpl(button, state);
        }

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~ClickStatus() = default;

    private:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        ClickStatus();

        // �����p���\�b�h
        void UpdateClickStateImpl();
        bool CheckClickImpl(const int button, const int state)
        {
            //���������茋�ʂ�Ԃ�
            return (clickData[button] & state);
        }

        std::unordered_map<int, int> clickData;          // �N���b�N���
    };
}
```
