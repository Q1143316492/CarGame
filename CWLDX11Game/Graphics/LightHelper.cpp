#include "LightHelper.h"

DirectionalLight LightHelper::DefaultDirectionalLight()
{
	DirectionalLight light;
	light.ambient = DirectX::XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	light.specular = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	light.direction = DirectX::XMFLOAT3(-0.577f, -0.577f, 0.577f);
	return light;
}

Material LightHelper::DefaultMaterial()
{
	Material material;
	material.ambient = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	material.diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
	return material;
}

