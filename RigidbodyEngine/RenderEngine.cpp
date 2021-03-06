#include "RenderEngine.h"
#include "Camera.h"

RenderEngine::RenderEngine(EntityManager* entityManager) {
	mEntityManager = entityManager;
}

RenderEngine::~RenderEngine() {
	// DON'T DELETE ENTITYMANAGER HERE
	delete mShaderManager;
}

void RenderEngine::InitializeDirectX(HWND windowHandle, UINT width, UINT height)
{
	mWindowHandle = windowHandle;
	mScreenWidth = width;
	mScreenHeight = height;
	HRESULT hr;
	UINT createDeviceFlags = 0;

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	ID3D11Device* direct3DDevice = nullptr;
	ID3D11DeviceContext* direct3DDeviceContext = nullptr;
	if (FAILED(hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &direct3DDevice, &mFeatureLevel, &direct3DDeviceContext)))
	{
		//throw GameException("D3D11CreateDevice() failed", hr);
	}

	if (FAILED(hr = direct3DDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&mDirect3DDevice))))
	{
		//throw GameException("ID3D11Device::QueryInterface() failed", hr);
	}

	if (FAILED(hr = direct3DDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&mDirect3DDeviceContext))))
	{
		//throw GameException("ID3D11Device::QueryInterface() failed", hr);
	}

	ReleaseObject(direct3DDevice);
	ReleaseObject(direct3DDeviceContext);

	mDirect3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, mMultiSamplingCount, &mMultiSamplingQualityLevels);
	if (mMultiSamplingQualityLevels == 0)
	{
		//throw GameException("Unsupported multi-sampling quality");
	}

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.Width = mScreenWidth;
	swapChainDesc.Height = mScreenHeight;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	if (mMultiSamplingEnabled)
	{
		swapChainDesc.SampleDesc.Count = mMultiSamplingCount;
		swapChainDesc.SampleDesc.Quality = mMultiSamplingQualityLevels - 1;
	}
	else
	{
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGIDevice* dxgiDevice = nullptr;
	if (FAILED(hr = mDirect3DDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice))))
	{
		//throw GameException("ID3D11Device::QueryInterface() failed", hr);
	}

	IDXGIAdapter *dxgiAdapter = nullptr;
	if (FAILED(hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter))))
	{
		ReleaseObject(dxgiDevice);
		//throw GameException("IDXGIDevice::GetParent() failed retrieving adapter.", hr);
	}

	IDXGIFactory2* dxgiFactory = nullptr;
	if (FAILED(hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory))))
	{
		ReleaseObject(dxgiDevice);
		ReleaseObject(dxgiAdapter);
		//throw GameException("IDXGIAdapter::GetParent() failed retrieving factory.", hr);
	}

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc;
	ZeroMemory(&fullScreenDesc, sizeof(fullScreenDesc));
	fullScreenDesc.RefreshRate.Numerator = mFrameRate;
	fullScreenDesc.RefreshRate.Denominator = 1;
	fullScreenDesc.Windowed = !mIsFullScreen;

	if (FAILED(hr = dxgiFactory->CreateSwapChainForHwnd(dxgiDevice, mWindowHandle, &swapChainDesc, &fullScreenDesc, nullptr, &mSwapChain)))
	{
		ReleaseObject(dxgiDevice);
		ReleaseObject(dxgiAdapter);
		ReleaseObject(dxgiFactory);
		//throw GameException("IDXGIDevice::CreateSwapChainForHwnd() failed.", hr);
	}

	ReleaseObject(dxgiDevice);
	ReleaseObject(dxgiAdapter);
	ReleaseObject(dxgiFactory);

	ID3D11Texture2D* backBuffer;
	if (FAILED(hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
	{
		//throw GameException("IDXGISwapChain::GetBuffer() failed.", hr);
	}

	backBuffer->GetDesc(&mBackBufferDesc);

	if (FAILED(hr = mDirect3DDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView)))
	{
		ReleaseObject(backBuffer);
		//throw GameException("IDXGIDevice::CreateRenderTargetView() failed.", hr);
	}

	ReleaseObject(backBuffer);

	if (mDepthStencilBufferEnabled)
	{
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.Width = mScreenWidth;
		depthStencilDesc.Height = mScreenHeight;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

		if (mMultiSamplingEnabled)
		{
			depthStencilDesc.SampleDesc.Count = mMultiSamplingCount;
			depthStencilDesc.SampleDesc.Quality = mMultiSamplingQualityLevels - 1;
		}
		else
		{
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
		}

		if (FAILED(hr = mDirect3DDevice->CreateTexture2D(&depthStencilDesc, nullptr, &mDepthStencilBuffer)))
		{
			//throw GameException("IDXGIDevice::CreateTexture2D() failed.", hr);
		}

		if (FAILED(hr = mDirect3DDevice->CreateDepthStencilView(mDepthStencilBuffer, nullptr, &mDepthStencilView)))
		{
			//throw GameException("IDXGIDevice::CreateDepthStencilView() failed.", hr);
		}
	}

	mDirect3DDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	mViewport.TopLeftX = 0.0f;
	mViewport.TopLeftY = 0.0f;
	mViewport.Width = static_cast<float>(mScreenWidth);
	mViewport.Height = static_cast<float>(mScreenHeight);
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;

	mDirect3DDeviceContext->RSSetViewports(1, &mViewport);

	mShaderManager = new ShaderManager(mDirect3DDevice);
}

void RenderEngine::LoadMesh(MeshRenderer* mesh) {
	string shaderName = mesh->GetShaderName();
	Shader* shader;
	shader = mShaderManager->GetShader("Basic");
	if (shaderName.empty()) {
		
	}
	shader->LoadShaderVertices(mDirect3DDevice, mesh);
}

void RenderEngine::Draw(double deltaTime) {
	FLOAT color[4];
	color[0] = 0.5f;
	color[1] = 0.5f;
	color[2] = 0.8f;
	color[3] = 1.0f;
	mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView, color);
	mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	vector<Entity*> meshes = mEntityManager->GetComponentEntities(string("MeshRenderer"));

	for (auto mesh = meshes.begin(); mesh != meshes.end(); mesh++) {
		MeshRenderer* renderer = (MeshRenderer*)(*mesh)->GetComponent("MeshRenderer");
		if (renderer != nullptr) {
			string shaderName = renderer->GetShaderName();
			Shader* shader;
			if (shaderName.empty()) {
				shader = mShaderManager->GetShader("Basic");
			}
			else {
				shader = mShaderManager->GetShader(shaderName);
			}

			shader->SetDevice(mDirect3DDeviceContext, renderer->GetVertexBuffer());
			ID3DX11EffectVariable* variable = shader->GetEffect()->GetVariableByName("WorldViewProjection");
			ID3DX11EffectMatrixVariable* matrix = variable->AsMatrix();
			Camera* camTrans = (Camera*)mEntityManager->GetEntityByName(string("MainCamera"))->GetComponent("Camera");
			//XMMATRIX temp = ((Transform*)(*mesh)->GetComponent(string("Transform")))->EvaluateTransform();
			XMMATRIX current = ((Transform*)(*mesh)->GetComponent(string("Transform")))->EvaluateTransform() * camTrans->View() * camTrans->Projection();
			matrix->SetMatrix(reinterpret_cast<const float*>(&current));
			shader->GetPass()->Apply(0, mDirect3DDeviceContext);

			mDirect3DDeviceContext->Draw(renderer->GetBufferSize(), 0);
		}
	}

	HRESULT hr = mSwapChain->Present(0, 0);
}