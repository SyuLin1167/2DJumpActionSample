// ピクセルシェーダーの入力
struct PS_INPUT
{
    float4 pos : SV_POSITION;       //座標
    float4 dif : COLOR0;            //ディフューズカラー
    float2 TexCoords0 : TEXCOORD0;  //テクスチャ座標
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
    float4 color0 : SV_TARGET0; // 色
};

// main関数
PS_OUTPUT main(PS_INPUT PSInput)
{
    PS_OUTPUT PSOutput;
    
	// 出力カラー
    PSOutput.color0 = PSInput.dif;
    
	// 出力パラメータを返す
    return PSOutput;
}
