#pragma once
#include"Math/Vector2.h"

using namespace math;

/// <summary>
/// �`��֘A
/// </summary>
namespace shape
{
    /// <summary>
    /// ��`
    /// </summary>
    struct Rect
    {
    public:
        Vector2<float> pos;     //���W(����)
        Vector2<float> size;    //�T�C�Y

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Rect() :pos(), size() {};

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="_pos">���W</param>
        /// <param name="_size">�T�C�Y</param>
        Rect(Vector2<float>& _pos, Vector2<float> _size) : pos(_pos), size(_size) {};

        /// <summary>
        /// ���S���W
        /// </summary>
        /// <returns>���S���W</returns>
        Vector2<float> Center() const
        {
            return pos + size.Half();
        }

        /// <summary>
        /// �����W
        /// </summary>
        /// <returns>x���W</returns>
        const float Left() const
        {
            return pos.x;
        }

        /// <summary>
        /// �E���W
        /// </summary>
        /// <returns>x���W+����</returns>
        const float Right() const
        {
            return pos.x + size.x;
        }

        /// <summary>
        /// ���_���W
        /// </summary>
        /// <returns>y���W</returns>
        const float Top() const
        {
            return pos.y;
        }

        /// <summary>
        /// ��Ӎ��W
        /// </summary>
        /// <returns>y���W+����</returns>
        const float Bottom() const
        {
            return pos.y + size.y;
        }
    };
}
