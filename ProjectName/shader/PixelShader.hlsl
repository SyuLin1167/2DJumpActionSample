// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
    float4 pos : SV_POSITION;       //���W
    float4 dif : COLOR0;            //�f�B�t���[�Y�J���[
    float2 TexCoords0 : TEXCOORD0;  //�e�N�X�`�����W
};

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
    float4 color0 : SV_TARGET0; // �F
};

// main�֐�
PS_OUTPUT main(PS_INPUT PSInput)
{
    PS_OUTPUT PSOutput;
    
	// �o�̓J���[
    PSOutput.color0 = PSInput.dif;
    
	// �o�̓p�����[�^��Ԃ�
    return PSOutput;
}
