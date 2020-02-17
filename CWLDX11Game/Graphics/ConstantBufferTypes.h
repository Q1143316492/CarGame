#pragma once

#include <DirectXMath.h>
#include "LightHelper.h"

struct CB_VS_vertexshader
{
	DirectX::XMMATRIX wvpMatrix;
	DirectX::XMMATRIX worldMatrix;	// 用于hlsl中更新法向量
};

struct CB_PS_pixelshader
{
	DirectionalLight dirLight;
	Material material;
	DirectX::XMFLOAT4 eyePos;
};