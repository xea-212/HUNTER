//───────────────────────────────────────
// テクスチャ＆サンプラー
//───────────────────────────────────────
Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

//───────────────────────────────────────
// コンスタントバッファ
//───────────────────────────────────────
cbuffer global
{
    float4x4 g_matWVP;
    float4x4 g_matNormalTrans;
    float4x4 g_matWorld;

    float4 g_vecLightDir;
    float4 g_vecDiffuse;
    float4 g_vecAmbient; // 今回は使わない
    float4 g_vecSpeculer;

    float4 g_vecCameraPosition;

    float g_shuniness;
    bool g_isTexture;
};

//───────────────────────────────────────
// 頂点シェーダ出力
//───────────────────────────────────────
struct VS_OUT
{
    float4 pos : SV_POSITION;
    float3 normal : TEXCOORD0;
    float2 uv : TEXCOORD1;
    float3 worldPos : TEXCOORD2;
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 Normal : NORMAL, float2 Uv : TEXCOORD)
{
    VS_OUT outData;

	// スクリーン座標
    outData.pos = mul(pos, g_matWVP);

	// 法線変換
    Normal.w = 0;
    Normal = mul(Normal, g_matNormalTrans);

    outData.normal = normalize(Normal.xyz);

	// ワールド座標
    float4 worldPos = mul(pos, g_matWorld);
    outData.worldPos = worldPos.xyz;

	// UV
    outData.uv = Uv;

    return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	//────────────────────
	// ベクトル準備
	//────────────────────

    float3 N = normalize(inData.normal);

	// ライト方向
    float3 L = normalize(-g_vecLightDir.xyz);

	// 視線方向
    float3 V = normalize(g_vecCameraPosition.xyz - inData.worldPos);

	//────────────────────
	// Diffuse
	//────────────────────

    // 法線とライト方向の内積
    float NdotL = saturate(dot(N, L));

    // 境界を柔らかく
    NdotL = pow(NdotL, 0.8f);

    // 影を真っ黒にしない
    NdotL = NdotL * 0.7f + 0.3f;

    // 明るさ
    float4 shade = float4(NdotL, NdotL, NdotL, 1.0f);

	//────────────────────
	// テクスチャ or マテリアルカラー
	//────────────────────

    float4 diffuse;

    if (g_isTexture)
    {
        diffuse = g_texture.Sample(g_sampler, inData.uv);
    }
    else
    {
        diffuse = g_vecDiffuse;
    }

	//────────────────────
	// 固定アンビエント
	// Mayaに依存しない環境光
	//────────────────────

    float4 ambient = float4(0.25f, 0.25f, 0.25f, 1.0f);

	//────────────────────
	// Blinn-Phong Specular
	//────────────────────

    float4 speculer = float4(0, 0, 0, 0);

    if (g_vecSpeculer.a > 0)
    {
		// Half Vector
        float3 H = normalize(L + V);

		// ハイライト計算
        float spec = pow(
			saturate(dot(N, H)),
			g_shuniness
		);

		// テカりを少し抑える
        spec *= 0.5f;

        speculer = spec * g_vecSpeculer;
    }

	//────────────────────
	// 最終カラー
	//────────────────────

    float4 finalColor =
		(diffuse * shade) +
		(diffuse * ambient) +
		speculer;

    finalColor.a = diffuse.a;

    return saturate(finalColor);
}