#include "stdafx.h"
#include "BasicSample.h"

BasicSample::BasicSample() {};
BasicSample::~BasicSample() {};
bool BasicSample::InitD3D(HWND hwnd)
{
	m_D3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	m_D3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	int count = m_D3d9->GetAdapterCount();

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = ScreenWeight;
	d3dpp.BackBufferHeight = ScreenHight;
	//d3dpp.BackBufferFormat = D3DFMT_X8B8G8R8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = false;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr = m_D3d9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_Device
	);


	if (FAILED(hr))
	{
		const wchar_t cap[] = L"error";

		switch (hr)
		{
		case D3DERR_DEVICELOST:
		{
			const wchar_t contents[] = L"DEVICELOST";
			::MessageBox(hwnd, contents, cap, 0);
			break;
		}
		case D3DERR_INVALIDCALL:
		{
			const wchar_t contents[] = L"INVALIDCALL";
			::MessageBox(hwnd, contents, cap, 0);
			break;
		}
		case D3DERR_NOTAVAILABLE:
		{
			const wchar_t contents[] = L"NOTAVAILABLE";
			::MessageBox(hwnd, contents, cap, 0);
			break;
		}
		case D3DERR_OUTOFVIDEOMEMORY:
		{
			const wchar_t contents[] = L"OUTOFVIDEOMEMORY";
			::MessageBox(hwnd, contents, cap, 0);
			break;
		}
		default:
		{
			const wchar_t contents[] = L"create device failed";
			::MessageBox(hwnd, contents, cap, 0);
			break;
		}
		}

		return false;
	}

	return true;
}

bool BasicSample::SetUp()
{
	return true;
}

void BasicSample::Display(float deltaTime)
{
	m_Device->Clear(0, 0, D3DCLEAR_TARGET, 0xffffffff, 1.0f, 0);
	m_Device->Present(0, 0, 0, 0);
}
void BasicSample::CleanUp()
{
	m_D3d9->Release();
	m_Device->Release();
}
