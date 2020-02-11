#pragma once

#include "GameObjects.h"

class Cylinder : public Model
{
public:
	virtual void InitializeMesh(Mesh &mesh);

	void SetRadus(float radius);
	void SetHeight(float height);
	void SetLevel(float level);
private:
	float radius;
	float height;
	float level;
};

