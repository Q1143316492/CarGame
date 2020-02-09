#include "LightHelper.hlsl"

cbuffer lightBuffer : register(b0)
{
	DirectionalLight g_DirectionalLight;		// 平行光
	Material g_Material;
	float3 g_EyePositionW;
	float g_Pad;
}

struct PS_INPUT
{
	float4 inPosition : SV_POSITION;
	float2 inTexCoord : TEXCOORD;
	float3 inNormal : NORMAL;
};

Texture2D objTexture : TEXTURE: register(t0);
SamplerState objSamplerState : SAMPLER: register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 pixelColor = objTexture.Sample(objSamplerState, input.inTexCoord);
	return pixelColor;
	//float3 sampleColor = input.inNormal;
	//float3 ambientLight = t_ambientLightColor * t_ambientLightStrength;
	//float3 finalColor = sampleColor * ambientLight;
	//return float4(finalColor, 1.0f);
	
	//float3 sampleColor = objTexture.Sample(objSamplerState, input.inTexCoord);
	//float3 ambientLight = ambientLightColor * ambientLightStrength;
	//float3 finalColor = sampleColor * ambientLight
	//return float4(sampleColor, 1.0f);

	// 顶点指向眼睛的向量
	float3 toEyeW = normalize(g_EyePositionW - input.inPosition);

	// 初始化为0 
	float4 ambient, diffuse, spec;
	float4 A, D, S;
	ambient = diffuse = spec = A = D = S = float4(0.0f, 0.0f, 0.0f, 0.0f);

	input.inNormal = normalize(input.inNormal);
	ComputeDirectionalLight(g_Material, g_DirectionalLight, input.inNormal, toEyeW, A, D, S);
	ambient += A;
	diffuse += D;
	spec += S;

	float4 litColor = pixelColor * (ambient + diffuse) + spec;
	litColor.a = g_Material.Diffuse.a * pixelColor.a;

	return litColor;
}