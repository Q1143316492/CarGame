#include "Box.h"

void Box::InitializeMesh(Mesh & mesh)
{
	GeometryFactory::CreateBox(mesh, m_Length, m_Length, m_Length);
}

void Box::SetBoxLength(float Length)
{
	this->m_Length = Length;
}
