#include "CollisionDetection.h"

bool CollisionDetection::CollisionDetectionModel(Model & a, Model & b)
{
	if (a.GetCollisionType() == CollisionType::COLLISION_TYPE_BOX &&
		b.GetCollisionType() == CollisionType::COLLISION_TYPE_BOX)
	{

		return false;
		XMFLOAT3 posA = a.GetPositionFloat3();
		XMFLOAT3 posB = b.GetPositionFloat3();
		
		// 先按照俯视图检测碰撞，反正车子还不会飞
		/*
		正方形1
		A1  D1  
		
		B1  C1

		正方形2
		A2  D2  
		
		B2  C2
		*/
		XMFLOAT2 A1(posA.x - a.GetCollisionWidthX() / 2, posA.z + a.GetCollisionWidthZ() / 2);
		XMFLOAT2 B1(posA.x - a.GetCollisionWidthX() / 2, posA.z - a.GetCollisionWidthZ() / 2);
		XMFLOAT2 C1(posA.x + a.GetCollisionWidthX() / 2, posA.z - a.GetCollisionWidthZ() / 2);
		XMFLOAT2 D1(posA.x + a.GetCollisionWidthX() / 2, posA.z + a.GetCollisionWidthZ() / 2);

		XMFLOAT2 A2(posB.x - b.GetCollisionWidthX() / 2, posB.z + b.GetCollisionWidthZ() / 2);
		XMFLOAT2 B2(posB.x - b.GetCollisionWidthX() / 2, posB.z - b.GetCollisionWidthZ() / 2);
		XMFLOAT2 C2(posB.x + b.GetCollisionWidthX() / 2, posB.z - b.GetCollisionWidthZ() / 2);
		XMFLOAT2 D2(posB.x + b.GetCollisionWidthX() / 2, posB.z + b.GetCollisionWidthZ() / 2);
		
		if (CollisionDetection::PointInRect(A2, A1, B1, C1, D1) ||
			CollisionDetection::PointInRect(B2, A1, B1, C1, D1) ||
			CollisionDetection::PointInRect(C2, A1, B1, C1, D1) ||
			CollisionDetection::PointInRect(D2, A1, B1, C1, D1))
		{
			return true;
		}
		return false;
	}
	return false;
}

bool CollisionDetection::PointInTrangle(XMFLOAT2 p, XMFLOAT2 a, XMFLOAT2 b, XMFLOAT2 c)
{
	float areaTot = CollisionDetection::GetTrangleArea(a, b, c);
	float areaT1 = CollisionDetection::GetTrangleArea(p, a, b);
	float areaT2 = CollisionDetection::GetTrangleArea(p, a, c);
	float areaT3 = CollisionDetection::GetTrangleArea(p, b, c);
	if (FLOAT_QEUAL(areaTot, areaT1 + areaT2 + areaT3))
	{
		return true;
	}
	return false;
}

bool CollisionDetection::PointInRect(XMFLOAT2 p, XMFLOAT2 a, XMFLOAT2 b, XMFLOAT2 c, XMFLOAT2 d)
{
	if (CollisionDetection::PointInTrangle(p, a, b, c) ||
		CollisionDetection::PointInTrangle(p, a, c, d))
	{
		return true;
	}
	return false;
}

float CollisionDetection::GetTrangleArea(XMFLOAT2 a, XMFLOAT2 b, XMFLOAT2 c)
{
	XMFLOAT2 v1(b.x - a.x, b.y - a.y);
	XMFLOAT2 v2(c.x - a.x, c.y - a.y);
	return v1.x * v2.y - v1.y * v2.x;
}
