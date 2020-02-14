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

void DefaultCar::CalculateTyresPosition(std::vector<XMFLOAT3> &vecPosition)
{
	vecPosition.clear();
	XMVECTOR left, right, forward, backward, pos;
	XMFLOAT3 tmp;
	left = this->GetLeftVector() * this->GetCollisionWidthX() / 2.0F;
	right = this->GetRightVector() * this->GetCollisionWidthX() / 2.0F;
	forward = this->GetForwardVector() * this->GetCollisionWidthZ() / 3.0F;
	backward = this->GetBackwardVector() * this->GetCollisionWidthZ() / 3.0F;
	
	// 左前轮
	pos = this->GetPositionVector() + forward + left;
	XMStoreFloat3(&tmp, pos);
	vecPosition.push_back(tmp);
	// 右前轮
	pos = this->GetPositionVector() + forward + right;
	XMStoreFloat3(&tmp, pos);
	vecPosition.push_back(tmp);
	// 左后轮
	pos = this->GetPositionVector() + backward + left;
	XMStoreFloat3(&tmp, pos);
	vecPosition.push_back(tmp);
	// 右后轮
	pos = this->GetPositionVector() + backward + right;
	XMStoreFloat3(&tmp, pos);
	vecPosition.push_back(tmp);
}

void DefaultCar::CalculateTyresRotation(std::vector<XMFLOAT3>& vecRotation, float tyreRotForward, float tyreRot)
{
	static float tyresRot = 0.0F; // 轮子转动 角度
	static float rotSpeed = 1.0F; // 轮子转动 每帧转一度

	static const float tyresForwardRotMax = MathTools::AngleChange(30.0F);
	static const float tyresForwardRotMin = MathTools::AngleChange(-30.0F);
	static float tyresForwardRot = 0.0F; // 前轮转向的角度
	static float tyresForwardSpeed = 0.05F; // 前轮转向回复的速度

	vecRotation.clear();
	XMFLOAT3 alltyreRot, forwardTyre;
	alltyreRot = this->GetRotationFloat3();

	// 圆柱到轮胎要转90度
	alltyreRot.z += MathTools::AngleChange(90.0F);

	// 轮子旋转，每次转一度
	tyresRot += tyreRotForward;
	alltyreRot.x += MathTools::AngleChange(tyresRot);
	if (tyresRot >= 360.0F)
	{
		tyresRot -= 360.0F;
	}
	if (tyresRot <= -360.0F)
	{
		tyresRot += 360.0F;
	}
	// 前轮转向
	forwardTyre = alltyreRot;
	tyresForwardRot += tyreRot;
	// 前轮转向恢复
	if (tyresForwardRot > 0.0F)
	{
		tyresForwardRot -= tyresForwardSpeed;
	}
	if (tyresForwardRot < 0.0F)
	{
		tyresForwardRot += tyresForwardSpeed;
	}

	if (tyresForwardRot > tyresForwardRotMax)
	{
		tyresForwardRot = tyresForwardRotMax;
	}
	if (tyresForwardRot < tyresForwardRotMin)
	{
		tyresForwardRot = tyresForwardRotMin;
	}
	forwardTyre.y += tyresForwardRot;

	vecRotation.push_back(forwardTyre);
	vecRotation.push_back(forwardTyre);
	vecRotation.push_back(alltyreRot);
	vecRotation.push_back(alltyreRot);
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