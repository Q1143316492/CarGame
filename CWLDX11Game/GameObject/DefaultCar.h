#pragma once

#include "../Graphics/Model.h"

class DefaultCar : public Model
{
public:
	virtual void InitializeMesh(Mesh &mesh);

	virtual void MoveForward(float speed);
	virtual void Movebackward(float speed);	
	virtual void TurnLeft(float speed);
	virtual void TurnRight(float speed);
};

