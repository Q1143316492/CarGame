#include "DefaultCar.h"

DefaultCar::DefaultCar()
{
	SetCollisionType(CollisionType::COLLISION_TYPE_BOX);
}

void DefaultCar::InitializeMesh(Mesh & mesh)
{
	Mesh carBody, carHat;
	static const float width = 0.5F;
	static const float height = 0.25F;
	static const float length = 1.0F;

	this->m_LengthX = width;
	this->m_LengthY = height;
	this->m_LengthZ = length;

	GeometryFactory::CreateBox(carBody, width, height, length);
	GeometryFactory::CreateBoxWithOffset(carHat, width * 0.75F, height * 0.75F, length * 0.5F, 
		0.0F, height * 0.75F, -length / 10.0F);

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