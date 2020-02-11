#include "Box.h"

Box::Box()
{
	SetCollisionType(CollisionType::COLLISION_TYPE_BOX);
}

void Box::InitializeMesh(Mesh & mesh)
{
	GeometryFactory::CreateBox(mesh, m_LengthX, m_LengthX, m_LengthX);
}

void Box::SetBoxLength(float Length)
{
	this->m_LengthX = this->m_LengthY = this->m_LengthZ = Length;
}
