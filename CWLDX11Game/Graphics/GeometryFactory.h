#pragma once
#include "Mesh.h"

class GeometryFactory {
public:
	static void CreateBox(Mesh &mesh, float lengthX, float lengthY, float lengthZ);
	static void CreateBoxWithOffset(Mesh &mesh, float lengthX, float lengthY, float lengthZ,
		float offsetx = 0.0F, float offsety = 0.0F, float offsetz = 0.0F);

	static void CreateDefaultCar(Mesh &mesh);
};

