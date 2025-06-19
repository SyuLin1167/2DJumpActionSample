struct VS_INPUT
{
    float3 pos : POSITION0; //���W
    float4 dif : COLOR0;    //�f�B�t���[�Y�J���[
    float4 spc : COLOR1;    //�X�y�L�����J���[
    float2 texCoords0 : TEXCOORD0;  //�e�N�X�`�����W
};

// ���_�V�F�[�_�[�̏o��
struct VS_OUTPUT
{
    float4 dif : COLOR0;    //�f�B�t���[�Y�J���[
    float2 texCoords0 : TEXCOORD0;  //�e�N�X�`�����W
    float4 pos : SV_POSITION;   //���W
};

// main�֐�
VS_OUTPUT main(VS_INPUT VSInput)
{
	// �o�̓p�����[�^�Z�b�g
    VS_OUTPUT VSOutput;

    VSOutput.pos.xyz = VSInput.pos.xyz;
    VSOutput.pos.w = 1.0f;
    VSOutput.texCoords0 = VSInput.texCoords0;
    VSOutput.dif = VSInput.dif;

	// �o�̓p�����[�^��Ԃ�
    return VSOutput;
}



