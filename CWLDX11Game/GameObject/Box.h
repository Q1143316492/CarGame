#pragma once

#include "GameObjects.h"

class Box : public Model
{
public:
	virtual void InitializeMesh(Mesh &mesh);

	void SetBoxLength(float Length);
private:
	float m_Length = 0.0F;
};

