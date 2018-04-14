#pragma once
#include <d3d11_1.h>
#include "ShaderManager.h"
#include "EntityManager.h"

#define ReleaseObject(object) if((object) != NULL) { object->Release(); object = NULL; }
 
class RenderEngine {
public:
	RenderEngine(EntityManager* entityManager);
	virtual ~RenderEngine();

	void InitializeDirectX(HWND windowHandle, UINT width, UINT height);
	void LoadMesh(MeshRenderer* mesh);
	void Draw(double deltaTime);

private:
	ShaderManager* mShaderManager;
	EntityManager* mEntityManager;

	UINT mScreenWidth;
	UINT mScreenHeight;

	HWND mWindowHandle;
	WNDCLASSEX mWindow;

	D3D_FEATURE_LEVEL mFeatureLevel;
	ID3D11Device1* mDirect3DDevice;
	ID3D11DeviceContext1* mDirect3DDeviceContext;
	IDXGISwapChain1* mSwapChain;

	UINT mFrameRate;
	bool mIsFullScreen;
	bool mDepthStencilBufferEnabled;
	bool mMultiSamplingEnabled;
	UINT mMultiSamplingCount;
	UINT mMultiSamplingQualityLevels;

	ID3D11Texture2D* mDepthStencilBuffer;
	D3D11_TEXTURE2D_DESC mBackBufferDesc;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mViewport;
};