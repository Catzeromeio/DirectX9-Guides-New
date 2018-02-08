#pragma once
#include "stdafx.h"
#include <d3dx9.h>

namespace d3d
{
	extern	int ScreenHight;
	extern int ScreenWeight;

	const D3DXCOLOR WHITE(D3DCOLOR_XRGB(255, 255, 255));
	const D3DXCOLOR BLACK(D3DCOLOR_XRGB(0, 0, 0));
	const D3DXCOLOR RED(D3DCOLOR_XRGB(255, 0, 0));
	const D3DXCOLOR GREEN(D3DCOLOR_XRGB(0, 255, 0));
	const D3DXCOLOR BLUE(D3DCOLOR_XRGB(0, 0, 255));

	struct Vertex
	{
		Vertex();
		Vertex(float x, float y, float z);
		float _x, _y, _z;
		static const DWORD FVF;
	};

	struct ColorVertex
	{
		ColorVertex();
		ColorVertex(float x, float y, float z, D3DCOLOR color);
		
		float _x, _y, _z;
		D3DCOLOR _color;
		static const DWORD FVF;
	};

	struct NormalVertex
	{
		NormalVertex();
		NormalVertex(float x, float y, float z, float nx, float ny, float nz);

		float _x, _y, _z;
		float _nx, _ny, _nz;
		static const DWORD FVF;
	};
}
