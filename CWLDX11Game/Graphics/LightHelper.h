#pragma once

#include <cstring>
#include <DirectXMath.h>

// �����
struct DirectionalLight
{
	DirectionalLight() = default;
	DirectionalLight(const DirectX::XMFLOAT4& _ambient, const DirectX::XMFLOAT4& _diffuse, const DirectX::XMFLOAT4& _specular,
		const DirectX::XMFLOAT3& _direction) :
		ambient(_ambient), diffuse(_diffuse), specular(_specular), direction(_direction), pad() {}

	DirectX::XMFLOAT4 ambient;		// �ɹ�Դ����Ļ����������
	DirectX::XMFLOAT4 diffuse;		// �ɹ�Դ�����������������
	DirectX::XMFLOAT4 specular;		// �ɹ�Դ����ĸ߹������, w = ���淴��ǿ��
	DirectX::XMFLOAT3 direction;
	float pad;
};

// ����������
struct Material
{
	Material() = default;
	Material(const DirectX::XMFLOAT4& _ambient, const DirectX::XMFLOAT4& _diffuse, const DirectX::XMFLOAT4& _specular,
		const DirectX::XMFLOAT4& _reflect) :
		ambient(_ambient), diffuse(_diffuse), specular(_specular), Reflect(_reflect) {}

	DirectX::XMFLOAT4 ambient; // �ɹ�Դ����Ļ����������
	DirectX::XMFLOAT4 diffuse; // �ɹ�Դ�����������������
	DirectX::XMFLOAT4 specular; // �ɹ�Դ����ĸ߹������, w = ���淴��ǿ��
	DirectX::XMFLOAT4 Reflect;
};

class LightHelper
{
public:
	static DirectionalLight DefaultDirectionalLight();
	static Material DefaultMaterial();

private:

};