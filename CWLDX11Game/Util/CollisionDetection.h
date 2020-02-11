#pragma once

#include "../Graphics/Model.h"
#include "../Macro.h"

// Åö×²¼ì²â°ïÖúÀà
class CollisionDetection
{
public:
	static bool CollisionDetectionModel(Model &a, Model &b);

	static bool PointInTrangle(XMFLOAT2 p, XMFLOAT2 a, XMFLOAT2 b, XMFLOAT2 c);
	static bool PointInRect(XMFLOAT2 p, XMFLOAT2 a, XMFLOAT2 b, XMFLOAT2 c, XMFLOAT2 d);

	static float GetTrangleArea(XMFLOAT2 a, XMFLOAT2 b, XMFLOAT2 c);
};

