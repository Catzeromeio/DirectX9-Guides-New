#pragma once
#include "BasicSample.h"

class SampleLight:public BasicSample
{
public:
	SampleLight();
	~SampleLight();

	virtual bool SetUp();
	virtual void Display(float deltaTime_s);
	virtual void CleanUp();
	void SetUpLights();

private:

	IDirect3DVertexBuffer9 * VB;
};

