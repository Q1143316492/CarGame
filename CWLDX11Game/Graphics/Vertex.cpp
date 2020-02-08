#include "Vertex.h"

void Vertex::SetPosition(float x, float y, float z)
{
	this->pos = DirectX::XMFLOAT3(x, y, z);
}

void Vertex::SetTexCoord(float u, float v)
{
	this->texCoord = DirectX::XMFLOAT2(u, v);
}

void Vertex::SetNormal(float nx, float ny, float nz)
{
	this->normal = DirectX::XMFLOAT3(nx, ny, nz);
}
