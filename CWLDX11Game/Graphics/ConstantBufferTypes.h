#pragma once

#include <DirectXMath.h>
#include "LightHelper.h"

struct CB_VS_vertexshader
{
	DirectX::XMMATRIX wvpMatrix;		// word * view * project
	DirectX::XMMATRIX worldMatrix;
};

struct CB_PS_pixelshader
{
	DirectionalLight dirLight;
	Material material;
	DirectX::XMFLOAT4 eyePos;
};