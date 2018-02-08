#pragma once
#include "stdafx.h"
#include "D3DUtility.h"
using namespace d3d;

class BasicSample
{
public:
	BasicSample();
	~BasicSample();

	virtual bool InitD3D(HWND hwnd);
	virtual bool SetUp();
	virtual void Display(float deltaTime_s);
	virtual void CleanUp();

protected:


	IDirect3D9 * m_D3d9;
	IDirect3DDevice9 * m_Device;
};
