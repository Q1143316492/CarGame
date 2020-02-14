#include "Graphics.h"

Graphics::~Graphics()
{

}

bool Graphics::Init(HWND hwnd, int width, int height)
{
	this->windowWidth = width;
	this->windowHeight = height;

	if (!InitDirectX(hwnd))
		return false;

	if (!InitShaders())
		return false;

	if (!InitScene())
		return false;

	return true;
}

void Graphics::RenderFrame()
{
	this->cb_ps_pixelshader.ApplyChanges();
	this->deviceContext->PSSetConstantBuffers(0, 1, this->cb_ps_pixelshader.GetAddressOf());

	float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);
	this->deviceContext->ClearDepthStencilView(this->depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// vertex shader
	this->deviceContext->IASetInputLayout(this->vertexshader.GetInputLayout());
	this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	this->deviceContext->RSSetState(this->rasterizerState.Get());
	this->deviceContext->OMSetDepthStencilState(this->depthStencilState.Get(), 0);

	// texture state
	// todo move to texture class
	this->deviceContext->PSSetSamplers(0, 1, this->samplerState.GetAddressOf());

	this->deviceContext->VSSetShader(vertexshader.GetShader(), NULL, 0);
	this->deviceContext->PSSetShader(pixelshader.GetShader(), NULL, 0);

	// todo
	//model.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
	// draw
	for (size_t i = 0; i < objects.size(); i++)
	{
		this->objects[i]->Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
	}

	this->swapchain->Present(1, NULL);
}

bool Graphics::InitDirectX(HWND hwnd)
{
	std::vector<AdapterData> adapters = AdapterReader::GetAdapters();

	if (adapters.size() < 1)
	{
		ErrorLogger::Log("No IDXGI Adapters found.");
		return false;
	}

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = windowWidth;
	scd.BufferDesc.Height = windowHeight;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hwnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(adapters[0].pAdapter, // IDXGI Adapter
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,												 // FOR SOFTWARE DRIVER TYPE
		NULL,												 // FLAGS FOR RUNTIME LAYERS
		NULL,												 // FEATURE LEVELS ARRAY
		0,													 // # OF FEATURE LEVELS IN ARRAY
		D3D11_SDK_VERSION,
		&scd,												 // Swapchain description
		this->swapchain.GetAddressOf(),						 // Swapchain Address
		this->device.GetAddressOf(),						 // Device Address
		NULL,												 // Supported feature level
		this->deviceContext.GetAddressOf());				 // Device Context Address

	HR_CHECKER1(hr, "Failed to create device and swapchain.");

	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	hr = this->swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	HR_CHECKER1(hr, "GetBuffer Failed.");

	hr = this->device->CreateRenderTargetView(backBuffer.Get(), NULL, this->renderTargetView.GetAddressOf());
	HR_CHECKER1(hr, "Failed to create render target view.");

	// Describe our Depth / Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = windowWidth;
	depthStencilDesc.Height = windowHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = this->device->CreateTexture2D(&depthStencilDesc, NULL, this->depthStencilBuffer.GetAddressOf());
	HR_CHECKER1(hr, "Failed to create depth stencil buffer.");

	hr = this->device->CreateDepthStencilView(this->depthStencilBuffer.Get(), NULL, this->depthStencilView.GetAddressOf());
	HR_CHECKER1(hr, "Failed to create depth stencil view.");

	this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), this->depthStencilView.Get());

	// Create depth stencil state
	D3D11_DEPTH_STENCIL_DESC depthstencildesc;
	ZeroMemory(&depthstencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthstencildesc.DepthEnable = true;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	hr = this->device->CreateDepthStencilState(&depthstencildesc, this->depthStencilState.GetAddressOf());
	HR_CHECKER1(hr, "Failed to create depth stencil state.");

	// Create the Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT) windowWidth;
	viewport.Height = (FLOAT) windowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// Set the Viewport
	this->deviceContext->RSSetViewports(1, &viewport);

	// Create Rasterizer State 
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	hr = this->device->CreateRasterizerState(&rasterizerDesc, this->rasterizerState.GetAddressOf());
	HR_CHECKER1(hr, "Failed to create rasterizer state.")

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
	HR_CHECKER1(hr, "Failed to create sampler state.");

	return true;
}

bool Graphics::InitShaders()
{
	std::wstring shaderfolder = L"";

#pragma region DetermineShaderPath
	if (IsDebuggerPresent() == TRUE)
	{
#ifdef _DEBUG //Debug Mode
#ifdef _WIN64 //x64
		shaderfolder = L"..\\x64\\Debug\\";
#else  //x86 (Win32)
		shaderfolder = L"..\\Debug\\";
#endif
#else //Release Mode
#ifdef _WIN64 //x64
		shaderfolder = L"..\\x64\\Release\\";
#else  //x86 (Win32)
		shaderfolder = L"..\\Release\\";
#endif
#endif
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"NORMAL", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};

	UINT numElements = ARRAYSIZE(layout);

	if (!vertexshader.Initialize(this->device, shaderfolder + L"vertexshader.cso", layout, numElements))
		return false;
	
	if (!pixelshader.Initialize(this->device, shaderfolder + L"pixelshader.cso"))
		return false;

	return true;
}

bool Graphics::InitScene()
{
	HRESULT hr;

	hr = this->cb_vs_vertexshader.Initialize(this->device.Get(), this->deviceContext.Get());
	HR_CHECKER1(hr, "Failed to initialize vertexshader constant buffer.");

	hr = this->cb_ps_pixelshader.Initialize(this->device.Get(), this->deviceContext.Get());
	HR_CHECKER1(hr, "Failed to initialize pixelshader constant buffer.");

	// 光照
	this->cb_ps_pixelshader.data.material = LightHelper::DefaultMaterial();
	this->cb_ps_pixelshader.data.dirLight = LightHelper::DefaultDirectionalLight();
	this->cb_ps_pixelshader.data.eyePos = XMFLOAT4(0.0f, 0.0f, -2.0f, 0.0f);

	// 模型
	
	sky.Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader, objects);
	
	GameMapHelper::InitMaze(this->device, this->deviceContext, this->cb_vs_vertexshader, objects, collisionObjects);

	INIT_MODEL1(!car.Initialize(this->device, this->deviceContext, L"Data\\Textures\\metal.jpg", this->cb_vs_vertexshader));
	objects.push_back(&car);

	for (int i = 0; i < 4; i++)
	{
		tyres[i] = new Cylinder();
		tyres[i]->SetRadus(0.25F);
		tyres[i]->SetHeight(0.1F);
		tyres[i]->SetLevel(20);
		INIT_MODEL1(!tyres[i]->Initialize(this->device, this->deviceContext, L"Data\\Textures\\tyre.png", this->cb_vs_vertexshader));
		objects.push_back(tyres[i]);
	}
	
	// 中途换材质
	/*
		ID3D11ShaderResourceView * texture = nullptr;
		HRESULT hr = DirectX::CreateWICTextureFromFile(this->gfx.device.Get(), L"Data\\Textures\\piano.png", nullptr, &texture);
		HR_CHECKER2(hr, "Failed to create wic texture from file.");
		this->gfx.objects[0]->SetTexture(texture);
	*/

	// camera
	camera.SetPosition(this->car.GetPositionVector());
	camera.SetProjectionValues(90.0f, static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 1000.0f);

	return true;
}
