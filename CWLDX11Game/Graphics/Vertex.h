#pragma once

#include <DirectXMath.h>

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz)
		: pos(x, y, z), texCoord(u, v), normal(nx, ny, nz) {}

	void SetPosition(float x, float y, float z);
	void AdjustPosition(float x, float y, float z);
	void SetTexCoord(float u, float v);
	void SetNormal(float nx, float ny, float nz);

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 texCoord;
	DirectX::XMFLOAT3 normal;
};