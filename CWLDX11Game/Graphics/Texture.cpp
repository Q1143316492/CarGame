#include "Texture.h"

bool Texture::InitTexture(Microsoft::WRL::ComPtr<ID3D11Device> &device, const wchar_t * texturePath)
{
	HRESULT hr;
	// Create sampler description for sampler state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = device->CreateSamplerState(&sampDesc, this->samplerState.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create sampler state.");
		return false;
	}
	// load texture
	hr = DirectX::CreateWICTextureFromFile(device.Get(), texturePath, nullptr, myTexture.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create wic texture from file.");
		return false;
	}
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture::GetTexture()
{
	return this->myTexture;
}

ID3D11ShaderResourceView **Texture::GetTextureAddressOf()
{
	return this->myTexture.GetAddressOf();
}

ID3D11SamplerState ** Texture::GetSampleStateAddressOf()
{
	return this->samplerState.GetAddressOf();
}
