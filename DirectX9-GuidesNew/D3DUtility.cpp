#include "stdafx.h"
#include"D3DUtility.h"

namespace d3d
{
	
	int	ScreenHight = 800;	
	int ScreenWeight = 800;

	Vertex::Vertex() {};
	Vertex::Vertex(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}
	const DWORD Vertex::FVF = D3DFVF_XYZ;

	ColorVertex::ColorVertex() {};
	ColorVertex::ColorVertex(float x, float y, float z, D3DCOLOR color)
	{
		_x = x;
		_y = y;
		_z = z;
		_color = color;
	}
	const DWORD ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	NormalVertex::NormalVertex() {};
	NormalVertex::NormalVertex(float x, float y, float z, float nx, float ny, float nz)
	{
		_x = x;
		_y = y;
		_z = z;
		_nx = nx;
		_ny = ny;
		_nz = nz;
	}
	const DWORD NormalVertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
}

