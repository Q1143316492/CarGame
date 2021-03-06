#include "SkyBox.h"

void SkyBoxTop::InitializeMesh(Mesh & mesh)
{
	mesh.init(4, 6);
	float w2 = SKY_BOX_LENGTH_X / 2, h2 = SKY_BOX_LENGTH_Y / 2, d2 = SKY_BOX_LENGTH_Z / 2;
	Vertex v[] =
	{
		Vertex( w2, h2 + MOVE_UP_OFFSET, -d2,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f),
		Vertex( w2, h2 + MOVE_UP_OFFSET,  d2,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f),
		Vertex(-w2, h2 + MOVE_UP_OFFSET,  d2,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f),
		Vertex(-w2, h2 + MOVE_UP_OFFSET, -d2,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f),
	};

	DWORD indexs[] =
	{
		0, 1, 2, 2, 3, 0
	};
	for (size_t i = 0; i < sizeof(v) / sizeof(Vertex); i++)
	{
		mesh.SetVerTexValue(i, v[i]);
	}
	for (size_t i = 0; i < sizeof(indexs) / sizeof(DWORD); i++)
	{
		mesh.SetIndexValue(i, indexs[i]);
	}
}

void SkyBoxLeft::InitializeMesh(Mesh & mesh)
{
	mesh.init(4, 6);
	float w2 = SKY_BOX_LENGTH_X / 2, h2 = SKY_BOX_LENGTH_Y / 2, d2 = SKY_BOX_LENGTH_Z / 2;
	Vertex v[] =
	{
		//Vertex(-w2, -h2 + MOVE_UP_OFFSET, -d2,  0.0f, 1.0f,     1.0f, 0.0f, 0.0f),
		//Vertex(-w2,  h2 + MOVE_UP_OFFSET, -d2,  0.0f, 0.0f,     1.0f, 0.0f, 0.0f),
		//Vertex(-w2,  h2 + MOVE_UP_OFFSET,  d2,  1.0f, 0.0f,     1.0f, 0.0f, 0.0f),
		//Vertex(-w2, -h2 + MOVE_UP_OFFSET,  d2,  1.0f, 1.0f,     1.0f, 0.0f, 0.0f),
		Vertex(-w2, -h2 + MOVE_UP_OFFSET, -d2,  0.0f, 1.0f,     0.0f, 1.0f, 0.0f),
		Vertex(-w2,  h2 + MOVE_UP_OFFSET, -d2,  0.0f, 0.0f,     0.0f, 1.0f, 0.0f),
		Vertex(-w2,  h2 + MOVE_UP_OFFSET,  d2,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f),
		Vertex(-w2, -h2 + MOVE_UP_OFFSET,  d2,  1.0f, 1.0f,     0.0f, 1.0f, 0.0f),
	};

	DWORD indexs[] =
	{
		0, 1, 2, 2, 3, 0,
	};
	for (size_t i = 0; i < sizeof(v) / sizeof(Vertex); i++)
	{
		mesh.SetVerTexValue(i, v[i]);
	}
	for (size_t i = 0; i < sizeof(indexs) / sizeof(DWORD); i++)
	{
		mesh.SetIndexValue(i, indexs[i]);
	}
}

void SkyBoxRight::InitializeMesh(Mesh & mesh)
{
	mesh.init(4, 6);
	float w2 = SKY_BOX_LENGTH_X / 2, h2 = SKY_BOX_LENGTH_Y / 2, d2 = SKY_BOX_LENGTH_Z / 2;
	Vertex v[] =
	{
		//Vertex( w2, -h2 + MOVE_UP_OFFSET,  d2,  0.0f, 1.0f,   -1.0f, 0.0f, 0.0f),
		//Vertex( w2,  h2 + MOVE_UP_OFFSET,  d2,  0.0f, 0.0f,   -1.0f, 0.0f, 0.0f),
		//Vertex( w2,  h2 + MOVE_UP_OFFSET, -d2,  1.0f, 0.0f,   -1.0f, 0.0f, 0.0f),
		//Vertex( w2, -h2 + MOVE_UP_OFFSET, -d2,  1.0f, 1.0f,   -1.0f, 0.0f, 0.0f),
		Vertex(w2, -h2 + MOVE_UP_OFFSET,  d2,  0.0f, 1.0f,   0.0f, 1.0f, 0.0f),
		Vertex(w2,  h2 + MOVE_UP_OFFSET,  d2,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f),
		Vertex(w2,  h2 + MOVE_UP_OFFSET, -d2,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f),
		Vertex(w2, -h2 + MOVE_UP_OFFSET, -d2,  1.0f, 1.0f,   0.0f, 1.0f, 0.0f),
	};

	DWORD indexs[] =
	{
		0, 1, 2, 2, 3, 0,
	};
	for (size_t i = 0; i < sizeof(v) / sizeof(Vertex); i++)
	{
		mesh.SetVerTexValue(i, v[i]);
	}
	for (size_t i = 0; i < sizeof(indexs) / sizeof(DWORD); i++)
	{
		mesh.SetIndexValue(i, indexs[i]);
	}
}

void SkyBoxBottom::InitializeMesh(Mesh & mesh)
{
	mesh.init(8, 12);
	float w2 = SKY_BOX_LENGTH_X / 2, h2 = SKY_BOX_LENGTH_Y / 2, d2 = SKY_BOX_LENGTH_Z / 2;
	Vertex v[] =
	{
		Vertex(-w2, -h2 + MOVE_UP_OFFSET, -d2,  0.0f, SKY_BOX_LENGTH_X,              0.0f, 1.0f, 0.0f),
		Vertex(-w2, -h2 + MOVE_UP_OFFSET,  d2,  0.0f, 0.0f,                          0.0f, 1.0f, 0.0f),
		Vertex( w2, -h2 + MOVE_UP_OFFSET,  d2,  SKY_BOX_LENGTH_X, 0.0f,              0.0f, 1.0f, 0.0f),
		Vertex( w2, -h2 + MOVE_UP_OFFSET, -d2,  SKY_BOX_LENGTH_X, SKY_BOX_LENGTH_X,  0.0f, 1.0f, 0.0f),

		Vertex(-w2, 0.0F, -d2,  0.0f, SKY_BOX_LENGTH_X,                              0.0f, 1.0f, 0.0f),
		Vertex(-w2, 0.0F,  d2,  0.0f, 0.0f,                                          0.0f, 1.0f, 0.0f),
		Vertex( w2, 0.0F,  d2,  SKY_BOX_LENGTH_X, 0.0f,                              0.0f, 1.0f, 0.0f),
		Vertex( w2, 0.0F, -d2,  SKY_BOX_LENGTH_X, SKY_BOX_LENGTH_X,                  0.0f, 1.0f, 0.0f),
	};

	DWORD indexs[] =
	{
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
	};
	for (size_t i = 0; i < sizeof(v) / sizeof(Vertex); i++)
	{
		mesh.SetVerTexValue(i, v[i]);
	}
	for (size_t i = 0; i < sizeof(indexs) / sizeof(DWORD); i++)
	{
		mesh.SetIndexValue(i, indexs[i]);
	}
}

void SkyBoxFront::InitializeMesh(Mesh & mesh)
{
	mesh.init(4, 6);
	float w2 = SKY_BOX_LENGTH_X / 2, h2 = SKY_BOX_LENGTH_Y / 2, d2 = SKY_BOX_LENGTH_Z / 2;
	Vertex v[] =
	{
		//Vertex(-w2, -h2 + MOVE_UP_OFFSET, d2,  0.0f, 1.0f,   0.0f, 0.0f, -1.0f),
		//Vertex(-w2,  h2 + MOVE_UP_OFFSET, d2,  0.0f, 0.0f,   0.0f, 0.0f, -1.0f),
		//Vertex( w2,  h2 + MOVE_UP_OFFSET, d2,  1.0f, 0.0f,   0.0f, 0.0f, -1.0f),
		//Vertex( w2, -h2 + MOVE_UP_OFFSET, d2,  1.0f, 1.0f,   0.0f, 0.0f, -1.0f),
		Vertex(-w2, -h2 + MOVE_UP_OFFSET, d2,  0.0f, 1.0f,   0.0f, 1.0f, 0.0f),
		Vertex(-w2,  h2 + MOVE_UP_OFFSET, d2,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f),
		Vertex( w2,  h2 + MOVE_UP_OFFSET, d2,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f),
		Vertex( w2, -h2 + MOVE_UP_OFFSET, d2,  1.0f, 1.0f,   0.0f, 1.0f, 0.0f),
	};
	DWORD indexs[] =
	{
		0, 1, 2, 2, 3, 0,
	};
	for (size_t i = 0; i < sizeof(v) / sizeof(Vertex); i++)
	{
		mesh.SetVerTexValue(i, v[i]);
	}
	for (size_t i = 0; i < sizeof(indexs) / sizeof(DWORD); i++)
	{
		mesh.SetIndexValue(i, indexs[i]);
	}
}

void SkyBoxBack::InitializeMesh(Mesh & mesh)
{
	mesh.init(4, 6);
	float w2 = SKY_BOX_LENGTH_X / 2, h2 = SKY_BOX_LENGTH_Y / 2, d2 = SKY_BOX_LENGTH_Z / 2;
	Vertex v[] =
	{
		//Vertex( w2, -h2 + MOVE_UP_OFFSET, -d2,  0.0f, 1.0f,   0.0f, 0.0f, 1.0f),
		//Vertex( w2,  h2 + MOVE_UP_OFFSET, -d2,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f),
		//Vertex(-w2,  h2 + MOVE_UP_OFFSET, -d2,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f),
		//Vertex(-w2, -h2 + MOVE_UP_OFFSET, -d2,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f),
		Vertex(w2, -h2 + MOVE_UP_OFFSET, -d2,  0.0f, 1.0f,   0.0f, 1.0f, 0.0f),
		Vertex(w2,  h2 + MOVE_UP_OFFSET, -d2,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f),
		Vertex(-w2,  h2 + MOVE_UP_OFFSET, -d2,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f),
		Vertex(-w2, -h2 + MOVE_UP_OFFSET, -d2,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f),
	};

	DWORD indexs[] =
	{
		0, 1, 2, 2, 3, 0,
	};
	for (size_t i = 0; i < sizeof(v) / sizeof(Vertex); i++)
	{
		mesh.SetVerTexValue(i, v[i]);
	}
	for (size_t i = 0; i < sizeof(indexs) / sizeof(DWORD); i++)
	{
		mesh.SetIndexValue(i, indexs[i]);
	}
}

bool SkyBox::Init(ID3D11Device * device, 
	ID3D11DeviceContext * deviceContext, 
	ConstantBuffer<CB_VS_vertexshader>& cb_vs_vertexshader,
	std::vector<Model*> &objects)
{
	skyboxtop = new SkyBoxTop();
	if (!skyboxtop->Initialize(device, deviceContext, L"Data\\Textures\\top.png", cb_vs_vertexshader))
	{
		return false;
	}
	skyboxbottom = new SkyBoxBottom();
	if (!skyboxbottom->Initialize(device, deviceContext, L"Data\\Textures\\grass.jpg", cb_vs_vertexshader))
	{
		return false;
	}
	skyboxleft = new SkyBoxLeft();
	if (!skyboxleft->Initialize(device, deviceContext, L"Data\\Textures\\left.png", cb_vs_vertexshader))
	{
		return false;
	}
	skyboxright = new SkyBoxRight();
	if (!skyboxright->Initialize(device, deviceContext, L"Data\\Textures\\right.png", cb_vs_vertexshader))
	{
		return false;
	}
	skyboxfront = new SkyBoxFront();
	if (!skyboxfront->Initialize(device, deviceContext, L"Data\\Textures\\front.png", cb_vs_vertexshader))
	{
		return false;
	}
	skyboxback = new SkyBoxBack();
	if (!skyboxback->Initialize(device, deviceContext, L"Data\\Textures\\back.png", cb_vs_vertexshader))
	{
		return false;
	}
	objects.push_back(skyboxtop);
	objects.push_back(skyboxbottom);
	objects.push_back(skyboxleft);
	objects.push_back(skyboxright);
	objects.push_back(skyboxfront);
	objects.push_back(skyboxback);
	return true;
}

void SkyBox::MoveSkyBox(Model * player)
{
	XMFLOAT3 pos = player->GetPositionFloat3();
	skyboxtop->SetPosition(pos.x, 0.0F, pos.z);
	skyboxleft->SetPosition(pos.x, 0.0F, pos.z);
	skyboxright->SetPosition(pos.x, 0.0F, pos.z);
	skyboxfront->SetPosition(pos.x, 0.0F, pos.z);
	skyboxback->SetPosition(pos.x, 0.0F, pos.z);
	// skyboxbottom->SetPosition(pos.x, 0.0F, pos.z);
}
