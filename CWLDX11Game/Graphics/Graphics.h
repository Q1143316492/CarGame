#pragma once

#include <vector>

#include "AdapterReader.h"
#include "Shaders.h"
#include "model.h"
#include "ConstantBuffer.h"
#include "Camera.h"
#include "Texture.h"
#include "LightHelper.h"
#include "../GameObject/SkyBox.h"

class Graphics
{
public:
	bool Init(HWND hwnd, int width, int height);
	void RenderFrame();

	Camera camera;
	std::vector<Model*> objects;
private:
	bool InitDirectX(HWND hwnd);
	bool InitShaders();
	bool InitScene();

public:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
private:
	VertexShader vertexshader;
	PixelShader pixelshader;
	ConstantBuffer<CB_VS_vertexshader> cb_vs_vertexshader;
	ConstantBuffer<CB_PS_pixelshader> cb_ps_pixelshader;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;

	int windowWidth = 0;
	int windowHeight = 0;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
};