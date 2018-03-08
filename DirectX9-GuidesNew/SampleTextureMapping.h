#pragma once
#include "BasicSample.h"

class SampleTextureMapping : public BasicSample
{
public:
	SampleTextureMapping();
	~SampleTextureMapping();

	virtual bool SetUp();
	virtual void Display(float deltaTime_s);
	virtual void CleanUp();

private:

};