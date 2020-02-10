#include "DefaultCar.h"

void DefaultCar::InitializeMesh(Mesh & mesh)
{
	Mesh carBody, carHat;
	GeometryFactory::CreateBox(carBody, 1.0F, 0.5F, 2.0F);
	GeometryFactory::CreateBoxWithOffset(carHat, 1.0F * 0.75F, 0.5F * 0.75F, 2.0F * 0.5F, 0.0F, 0.4F, -0.1F);

	UINT vertexSize = carBody.GetVertexSize() + carHat.GetVertexSize();
	UINT indexSize = carBody.GetIndexSize() + carHat.GetIndexSize();

	mesh.init(vertexSize, indexSize);
	// car body
	for (UINT i = 0; i < carBody.GetVertexSize(); i++)
	{
		mesh.SetVerTexValue(i, carBody.GetVertex(i));
	}
	for (UINT i = 0; i < carBody.GetIndexSize(); i++)
	{
		mesh.SetIndexValue(i, carBody.GetIndex(i));
	}
	// car hat
	for (UINT i = 0; i < carHat.GetVertexSize(); i++)
	{
		mesh.SetVerTexValue(i + carBody.GetVertexSize(), carHat.GetVertex(i));
	}
	for (UINT i = 0; i < carHat.GetIndexSize(); i++)
	{
		mesh.SetIndexValue(i + carBody.GetIndexSize(), carHat.GetIndex(i) + carBody.GetVertexSize());
	}
}

void DefaultCar::MoveForward(float speed)
{
	XMVECTOR vec = this->GetForwardVector() * speed;
	this->AdjustPosition(vec);
}

void DefaultCar::Movebackward(float speed)
{
	XMVECTOR vec = this->GetBackwardVector() * speed;
	this->AdjustPosition(vec);
}

void DefaultCar::TurnLeft(float speed)
{
	this->AdjustRotation(0.0F, -speed, 0.0F);
}

void DefaultCar::TurnRight(float speed)
{
	this->AdjustRotation(0.0F, speed, 0.0F);
}

void DefaultCar::MoveLeft(float speed)
{
	XMVECTOR vec = this->GetLeftVector() * speed;
	this->AdjustPosition(vec);
}

void DefaultCar::MoveRight(float speed)
{
	XMVECTOR vec = this->GetRightVector() * speed;
	this->AdjustPosition(vec);
}