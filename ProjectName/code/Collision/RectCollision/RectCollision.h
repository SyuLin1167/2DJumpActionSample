#pragma once
#include"Shape/Rect.h"
#include"CollisionBase/CollisionBase.h"

/// <summary>
/// �����蔻��֘A
/// </summary>
namespace collision
{
    /// <summary>
    /// ��`�����蔻��
    /// </summary>
    class RectCollision final :public CollisionBase
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        RectCollision() = default;

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="_pos">���W</param>
        /// <param name="_size">�T�C�Y</param>
        /// <param name="_velocity">����</param>
        RectCollision(Vector2<float>& _pos, Vector2<float>& _size, Vector2<float>& _velocity);

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="_rect">��`</param>
        /// <param name="_velocity">����</param>
        RectCollision(shape::Rect _rect, Vector2<float>& _velocity);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~RectCollision() = default;

        /// <summary>
        /// �f�B�X�p�b�`
        /// </summary>
        /// <param name="_handle">�C�x���g�p�n���h��</param>
        /// <param name="_other">�Ώۂ̃R���W����</param>
        void Dispatch(uint64_t _handle, CollisionBase* _other) override;

        /// <summary>
        /// ���g�̃x�[�X�̋�`
        /// </summary>
        /// <returns>�x�[�X�̋�`</returns>
        const shape::Rect MyBaseRect()
        {
            baseRect.pos = pos;
            baseRect.size = size;
            return baseRect;
        }

        /// <summary>
        /// ���g�̃X�C�[�v��`
        /// </summary>
        /// <returns>�X�C�[�v��`</returns>
        const shape::Rect SweptRect()
        {
            CalcSweptRect();
            return sweptRect;
        }

        /// <summary>
        /// �����蔻�菈��(Map)
        /// </summary>
        /// <param name="_other">Map�����蔻��</param>
        /// <param name="_info">����Ώې�p�̓����蔻����</param>
        void ColliderWith(MapCollision& _other, TargetColInfo& _info) override;

        /// <summary>
        /// �����蔻�菈��(Rect)
        /// </summary>
        /// <param name="_other">Rect�����蔻��</param>
        /// <param name="_info">����Ώې�p�̓����蔻����
        void ColliderWith(RectCollision& _other, TargetColInfo& _info) override;

        /// <summary>
        /// �������Z�o
        /// </summary>
        /// <param name="_other"></param>
        void CalcDiff(const RectCollision& _other);

        /// <summary>
        /// ����̂��߂̍����̏��O
        /// </summary>
        /// <param name="_xx">������</param>
        /// <param name="_xy">�E����</param>
        /// <param name="_yx">�㔻��</param>
        /// <param name="_yy">������</param>
        void ExclDiff(bool _xx, bool _xy, bool _yx, bool _yy);

        /// <summary>
        /// �����߂�����
        /// </summary>
        void PushBack();

        /// <summary>
        /// �Փ˔���(Rect)
        /// </summary>
        /// <param name="_otherRect">����Rect</param>
        /// <returns>�Փ˂��Ă��邩</returns>
        bool HasColliderRect(const shape::Rect& _otherRect)
        {
            return sweptRect.Left() < _otherRect.Right() &&
                sweptRect.Right() > _otherRect.Left() &&
                sweptRect.Top() < _otherRect.Bottom() &&
                sweptRect.Bottom() > _otherRect.Top();
        }

        /// <summary>
        /// ���x�ȗ��\��
        /// </summary>
        /// <returns>���ꂼ��̎��ɑ΂���-1,0,1�ł̑��x�\��</returns>
        Vector2<int> SignVelocity()
        {
            return {
                (velocity.x > 0) - (velocity.x < 0),
                (velocity.y > 0) - (velocity.y < 0)
            };
        }

        /// <summary>
        /// ���g�̌`��
        /// </summary>
        /// <returns>Rect</returns>
        ShapeTag MyShape() const override
        {
            return ShapeTag::RECT;
        }

    private:
        /// <summary>
        /// �X�C�[�v��`�̎Z�o
        /// </summary>
        void CalcSweptRect();

        Vector2<float>& pos;      //���W
        Vector2<float>& size;     //�T�C�Y
        Vector2<float>& velocity; //���x
        shape::Rect baseRect;           //�x�[�X��`
        shape::Rect sweptRect;          //�X�C�[�v��`
        Vector2<float> diffX;     //X������
        Vector2<float> diffY;     //Y������
    };
}
