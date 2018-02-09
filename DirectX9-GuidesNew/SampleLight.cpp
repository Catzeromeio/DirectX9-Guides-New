#include "stdafx.h"
#include "SampleLight.h"

SampleLight::SampleLight()
{
}

SampleLight::~SampleLight()
{
}

bool SampleLight::SetUp()
{
	// Turn off culling
	m_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// Turn on the zbuffer
	m_Device->SetRenderState(D3DRS_ZENABLE, TRUE);

	// Create the vertex buffer.
	if (FAILED(m_Device->CreateVertexBuffer(50 * 2 * sizeof(NormalVertex),
		0, NormalVertex::FVF,
		D3DPOOL_DEFAULT, &VB, NULL)))
	{
		return E_FAIL;
	}

	// Fill the vertex buffer. We are algorithmically generating a cylinder
	// here, including the normals, which are used for lighting.
	

	NormalVertex *v; 
	VB-> Lock(0, 0, (void **)&v, 0);
	v[0] = NormalVertex(-1.0f, 0, -1.0f, 0, 1, 0);
	v[1] = NormalVertex(1.0f, 0, -1.0f, 0, 1, 0);
	v[2] = NormalVertex(0, 0, 1.0f, 0, 1, 0);
	VB-> Unlock();
	

	//position and aim camera
	D3DXVECTOR3 position(0, 0, -5.0f);
	D3DXVECTOR3 target(0, 0, 0);
	D3DXVECTOR3 up(0, 1.0f, 0);

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	m_Device->SetTransform(D3DTS_VIEW, &V);

	//set projection matrix
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, (float)ScreenWeight / (float)ScreenHight, 1, 1000.0f);
	m_Device->SetTransform(D3DTS_PROJECTION, &proj);

	m_Device->SetFVF(NormalVertex::FVF);

	SetUpLights();


	return true;
}

void SampleLight::Display(float deltaTime)
{
	if (m_Device)
	{
		//spin the cube
		D3DXMATRIX Rx, Ry;
		static float y = 0.0f;

		D3DXMatrixRotationX(&Rx, y);
		D3DXMatrixRotationY(&Ry, 0);
		y += deltaTime;
		if (y >= 2 * D3DX_PI)
			y = 0;

		D3DXMATRIX R = Rx * Ry;

		m_Device->SetTransform(D3DTS_WORLD, &R);

		//draw the scene
		m_Device->Clear(0, 0, D3DCLEAR_TARGET, 0xffffff, 1.0f, 0);
		m_Device->BeginScene();
		m_Device->SetStreamSource(0, VB, 0, sizeof(NormalVertex));
		m_Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);

		m_Device->EndScene();
		m_Device->Present(0, 0, 0, 0);
	}
}
void SampleLight::SetUpLights()
{
	// Set up a material. The material here just has the diffuse and ambient
	// colors set to yellow. Note that only one material can be used at a time.
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	m_Device->SetMaterial(&mtrl);

	// Set up a white, directional light, with an oscillating direction.
	// Note that many Lights may be active at a time (but each one slows down
	// the rendering of our scene). However, here we are just using one. Also,
	// we need to set the D3DRS_LIGHTING renderstate to enable lighting
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	vecDir = D3DXVECTOR3(1.0,
		1.0f,
		0);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 1000.0f;
	m_Device->SetLight(0, &light);
	m_Device->LightEnable(0, TRUE);
	m_Device->SetRenderState(D3DRS_LIGHTING, TRUE);
 }

void SampleLight::CleanUp()
{
	VB->Release();
	BasicSample::CleanUp();
}
