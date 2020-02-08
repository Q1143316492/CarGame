#pragma once

#include <cstring>
#include <DirectXMath.h>

// 方向光
struct DirectionalLight
{
	DirectionalLight() = default;
	DirectionalLight(const DirectX::XMFLOAT4& _ambient, const DirectX::XMFLOAT4& _diffuse, const DirectX::XMFLOAT4& _specular,
		const DirectX::XMFLOAT3& _direction) :
		ambient(_ambient), diffuse(_diffuse), specular(_specular), direction(_direction), pad() {}

	DirectX::XMFLOAT4 ambient;		// 由光源发射的环境光的数量
	DirectX::XMFLOAT4 diffuse;		// 由光源发射的漫反射光的数量
	DirectX::XMFLOAT4 specular;		// 由光源发射的高光的数量, w = 镜面反射强度
	DirectX::XMFLOAT3 direction;
	float pad;
};

// 物体表面材质
struct Material
{
	Material() = default;
	Material(const DirectX::XMFLOAT4& _ambient, const DirectX::XMFLOAT4& _diffuse, const DirectX::XMFLOAT4& _specular,
		const DirectX::XMFLOAT4& _reflect) :
		ambient(_ambient), diffuse(_diffuse), specular(_specular), Reflect(_reflect) {}

	DirectX::XMFLOAT4 ambient; // 由光源发射的环境光的数量
	DirectX::XMFLOAT4 diffuse; // 由光源发射的漫反射光的数量
	DirectX::XMFLOAT4 specular; // 由光源发射的高光的数量, w = 镜面反射强度
	DirectX::XMFLOAT4 Reflect;
};

class LightHelper
{
public:
	static DirectionalLight DefaultDirectionalLight();
	static Material DefaultMaterial();

private:

};