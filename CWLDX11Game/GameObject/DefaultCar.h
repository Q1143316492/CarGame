#pragma once

#include "../Graphics/Model.h"

class DefaultCar : public Model
{
public:
	DefaultCar();
	
	virtual void InitializeMesh(Mesh &mesh);

	virtual void MoveForward(float speed);
	virtual void Movebackward(float speed);

	virtual void MoveLeft(float speed);
	virtual void MoveRight(float speed);

	virtual void TurnLeft(float speed);
	virtual void TurnRight(float speed);

	void CalculateTyresPosition(std::vector<XMFLOAT3> &vecPosition); 
	void CalculateTyresRotation(std::vector<XMFLOAT3> &vecRotation, float tyreRotForward, float tyreRot);
};

