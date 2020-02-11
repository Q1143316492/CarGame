#pragma once
#include "Mesh.h"
#include "../Util/MathTools.h"

#include <vector>

class GeometryFactory {
public:
	static void CreateBox(Mesh &mesh, float lengthX, float lengthY, float lengthZ);
	static void CreateBoxWithOffset(Mesh &mesh, float lengthX, float lengthY, float lengthZ,
		float offsetx = 0.0F, float offsety = 0.0F, float offsetz = 0.0F);

	static void CreateCylinder(Mesh & mesh, float radius, float height, float level);

	static void Test(Mesh &mesh);

};