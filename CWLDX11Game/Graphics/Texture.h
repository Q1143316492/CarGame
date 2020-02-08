#pragma once

#include "../Util/ErrorLogger.h"
#include <wrl/client.h>
#include <d3d11.h>
#include <WICTextureLoader.h>

// todo bug
class Texture {
public:
	bool InitTexture(Microsoft::WRL::ComPtr<ID3D11Device> &device, const wchar_t *texturePath);
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture();
	ID3D11ShaderResourceView ** GetTextureAddressOf();
	ID3D11SamplerState ** GetSampleStateAddressOf();
private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> myTexture;
};