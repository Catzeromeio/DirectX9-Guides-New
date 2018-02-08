#pragma once
#include"BasicSample.h"

class SampleRotateCube :public BasicSample
{
public:
	SampleRotateCube();
	~SampleRotateCube();

	virtual bool SetUp();
	virtual void Display(float deltaTime_s);
	virtual void CleanUp();

	IDirect3DVertexBuffer9 * VB = 0;
	IDirect3DIndexBuffer9 * IB = 0;
private:

};


