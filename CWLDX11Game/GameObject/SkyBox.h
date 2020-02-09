#pragma once

#include <vector>
#include "../Graphics/Model.h"

#define SKY_BOX_LENGTH_X 100.0F
#define SKY_BOX_LENGTH_Y 100.0F
#define SKY_BOX_LENGTH_Z 100.0F
#define MOVE_UP_OFFSET (SKY_BOX_LENGTH_Y / 3.0F)

class SkyBoxTop : public Model
{
public:
	virtual void InitializeMesh(Mesh &mesh);
};

class SkyBoxBottom : public Model
{
public:
	virtual void InitializeMesh(Mesh &mesh);
};


class SkyBoxLeft : public Model
{
public:
	virtual void InitializeMesh(Mesh &mesh);
};

class SkyBoxRight : public Model
{
public:
	virtual void InitializeMesh(Mesh &mesh);
};

class SkyBoxFront : public Model
{
public:
	virtual void InitializeMesh(Mesh &mesh);
};

class SkyBoxBack : public Model
{
public:
	virtual void InitializeMesh(Mesh &mesh);
};

class SkyBox {
public:
	bool Init(ID3D11Device * device, 
		ID3D11DeviceContext * deviceContext, 
		ConstantBuffer<CB_VS_vertexshader>& cb_vs_vertexshader,
		std::vector<Model*> &objects);

	Model* BoxTop;
};