#pragma once

#include "GameObjects.h"

class Box : public Model
{
public:
	Box();

	virtual void InitializeMesh(Mesh &mesh);

	void SetBoxLength(float Length);

};

