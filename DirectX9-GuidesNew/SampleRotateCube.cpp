#include "stdafx.h"
#include "SampleRotateCube.h"

SampleRotateCube::SampleRotateCube()
{
}

SampleRotateCube::~SampleRotateCube()
{
}

bool SampleRotateCube::SetUp()
{
	m_Device->CreateVertexBuffer(8 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &VB, 0);
	m_Device->CreateIndexBuffer(36 * sizeof(DWORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	//fill data
	Vertex* vertices = 0;
	VB->Lock(0, 0, (void **)&vertices, 0);
	//vetertices of  unit cube
	vertices[0] = Vertex(-1.0f, -1.0f, -1.0f);
	vertices[1] = Vertex(-1.0f, 1.0f, -1.0f);
	vertices[2] = Vertex(1.0f, 1.0f, -1.0f);
	vertices[3] = Vertex(1.0f, -1.0f, -1.0f);
	vertices[4] = Vertex(-1.0f, -1.0f, 1.0f);
	vertices[5] = Vertex(-1.0f, 1.0f, 1.0f);
	vertices[6] = Vertex(1.0f, 1.0f, 1.0f);
	vertices[7] = Vertex(1.0f, -1.0f, 1.0f);
	VB->Unlock();

	//define triangles of the cube
	WORD* indices = 0;
	IB->Lock(0, 0, (void **)&indices, 0);
	//front
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;
	//back
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;
	//left
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;
	//right
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;
	//top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;
	//botton
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;
	IB->Unlock();

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

	//set render model
	m_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_Device->SetFVF(Vertex::FVF);

	return true;
}

void SampleRotateCube::Display(float deltaTime)
{
	if (m_Device)
	{
		//spin the cube
		D3DXMATRIX Rx, Ry;
		static float y = 0.0f;

		D3DXMatrixRotationX(&Rx, y);
		D3DXMatrixRotationY(&Ry, y);
		y += deltaTime;
		if (y >= 2 * D3DX_PI)
			y = 0;

		D3DXMATRIX R = Rx * Ry;

		m_Device->SetTransform(D3DTS_WORLD, &R);

		//draw the scene
		m_Device->Clear(0, 0, D3DCLEAR_TARGET, 0xffffff, 1.0f, 0);
		m_Device->BeginScene();
		m_Device->SetStreamSource(0, VB, 0, sizeof(Vertex));
		m_Device->SetIndices(IB);
		m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

		m_Device->EndScene();
		m_Device->Present(0, 0, 0, 0);
	}
}

void SampleRotateCube::CleanUp()
{
	IB->Release();
	VB->Release();

	BasicSample::CleanUp();
}