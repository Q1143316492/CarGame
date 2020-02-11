#include "Cylinder.h"

void Cylinder::InitializeMesh(Mesh & mesh)
{
	GeometryFactory::CreateCylinder(mesh, radius, height, level);
}

void Cylinder::SetRadus(float radius)
{
	this->radius = radius;
}

void Cylinder::SetHeight(float height)
{
	this->height = height;
}

void Cylinder::SetLevel(float level)
{
	this->level = level;
}
