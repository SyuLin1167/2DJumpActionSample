struct VS_INPUT
{
    float3 pos : POSITION0; //座標
    float4 dif : COLOR0;    //ディフューズカラー
    float4 spc : COLOR1;    //スペキュラカラー
    float2 texCoords0 : TEXCOORD0;  //テクスチャ座標
};

// 頂点シェーダーの出力
struct VS_OUTPUT
{
    float4 dif : COLOR0;    //ディフューズカラー
    float2 texCoords0 : TEXCOORD0;  //テクスチャ座標
    float4 pos : SV_POSITION;   //座標
};

// main関数
VS_OUTPUT main(VS_INPUT VSInput)
{
	// 出力パラメータセット
    VS_OUTPUT VSOutput;

    VSOutput.pos.xyz = VSInput.pos.xyz;
    VSOutput.pos.w = 1.0f;
    VSOutput.texCoords0 = VSInput.texCoords0;
    VSOutput.dif = VSInput.dif;

	// 出力パラメータを返す
    return VSOutput;
}



