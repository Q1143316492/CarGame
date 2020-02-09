#include "GeometryFactory.h"

void GeometryFactory::CreateBox(Mesh &mesh, float lengthX, float lengthY, float lengthZ)
{
	mesh.init(24, 36);
	float w2 = lengthX / 2, h2 = lengthY / 2, d2 = lengthZ / 2;
	Vertex v[] =
	{
		// 右
		Vertex(w2, -h2, -d2,  0.0f, 1.0f,     1.0f, 0.0f, 0.0f),
		Vertex(w2,  h2, -d2,  0.0f, 0.0f,     1.0f, 0.0f, 0.0f),
		Vertex(w2,  h2,  d2,  1.0f, 0.0f,     1.0f, 0.0f, 0.0f),
		Vertex(w2, -h2,  d2,  1.0f, 1.0f,     1.0f, 0.0f, 0.0f),

		// 左
		Vertex(-w2, -h2, d2, 0.0f, 1.0f,   -1.0f, 0.0f, 0.0f),
		Vertex(-w2, h2, d2, 0.0f, 0.0f,    -1.0f, 0.0f, 0.0f),
		Vertex(-w2, h2, -d2, 1.0f, 0.0f,   -1.0f, 0.0f, 0.0f),
		Vertex(-w2, -h2, -d2, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f),

		// 上
		Vertex(-w2, h2, -d2, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f),
		Vertex(-w2, h2,  d2, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f),
		Vertex(w2, h2,  d2, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f),
		Vertex(w2, h2, -d2, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f),

		// 下
		Vertex(w2, -h2, -d2, 0.0f, 1.0f,    0.0f, -1.0f, 0.0f),
		Vertex(w2, -h2, d2, 0.0f, 0.0f,    0.0f, -1.0f, 0.0f),
		Vertex(-w2, -h2, d2, 1.0f, 0.0f,   0.0f, -1.0f, 0.0f),
		Vertex(-w2, -h2, -d2, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f),

		// 背面
		Vertex(w2, -h2, d2, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f),
		Vertex(w2, h2,  d2, 0.0f, 0.0f,     0.0f, 0.0f, 1.0f),
		Vertex(-w2, h2, d2, 1.0f, 0.0f,    0.0f, 0.0f, 1.0f),
		Vertex(-w2, -h2, d2, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f),

		// 正面
		Vertex(-w2, -h2, -d2, 0.0f, 1.0f,   0.0f, 0.0f, -1.0f),
		Vertex(-w2, h2, -d2, 0.0f, 0.0f,    0.0f, 0.0f, -1.0f),
		Vertex(w2, h2, -d2, 1.0f, 0.0f,     0.0f, 0.0f, -1.0f),
		Vertex(w2, -h2, -d2, 1.0f, 1.0f,    0.0f, 0.0f, -1.0f),
	};

	DWORD indexs[] =
	{
		0, 1, 2, 2, 3, 0,		// 右面(+X面)
		4, 5, 6, 6, 7, 4,		// 左面(-X面)
		8, 9, 10, 10, 11, 8,	// 顶面(+Y面)
		12, 13, 14, 14, 15, 12,	// 底面(-Y面)
		16, 17, 18, 18, 19, 16, // 背面(+Z面)
		20, 21, 22, 22, 23, 20	// 正面(-Z面)
	};
	for (size_t i = 0; i < sizeof(v) / sizeof(Vertex); i++)
	{
		mesh.SetVerTexValue(i, v[i]);
	}
	for (size_t i = 0; i < sizeof(indexs) / sizeof(DWORD); i++)
	{
		mesh.SetIndexValue(i, indexs[i]);
	}
}

void GeometryFactory::CreateBoxWithOffset(Mesh &mesh, float lengthX, float lengthY, float lengthZ, 
	float offsetx, float offsety, float offsetz)
{
	mesh.init(24, 36);
	float w2 = lengthX / 2, h2 = lengthY / 2, d2 = lengthZ / 2;
	Vertex v[] =
	{
		// 右
		Vertex(w2, -h2, -d2,  0.0f, 1.0f,     1.0f, 0.0f, 0.0f),
		Vertex(w2,  h2, -d2,  0.0f, 0.0f,     1.0f, 0.0f, 0.0f),
		Vertex(w2,  h2,  d2,  1.0f, 0.0f,     1.0f, 0.0f, 0.0f),
		Vertex(w2, -h2,  d2,  1.0f, 1.0f,     1.0f, 0.0f, 0.0f),

		// 左
		Vertex(-w2, -h2, d2, 0.0f, 1.0f,   -1.0f, 0.0f, 0.0f),
		Vertex(-w2, h2, d2, 0.0f, 0.0f,    -1.0f, 0.0f, 0.0f),
		Vertex(-w2, h2, -d2, 1.0f, 0.0f,   -1.0f, 0.0f, 0.0f),
		Vertex(-w2, -h2, -d2, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f),

		// 上
		Vertex(-w2, h2, -d2, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f),
		Vertex(-w2, h2,  d2, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f),
		Vertex(w2, h2,  d2, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f),
		Vertex(w2, h2, -d2, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f),

		// 下
		Vertex(w2, -h2, -d2, 0.0f, 1.0f,    0.0f, -1.0f, 0.0f),
		Vertex(w2, -h2, d2, 0.0f, 0.0f,    0.0f, -1.0f, 0.0f),
		Vertex(-w2, -h2, d2, 1.0f, 0.0f,   0.0f, -1.0f, 0.0f),
		Vertex(-w2, -h2, -d2, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f),

		// 背面
		Vertex(w2, -h2, d2, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f),
		Vertex(w2, h2,  d2, 0.0f, 0.0f,     0.0f, 0.0f, 1.0f),
		Vertex(-w2, h2, d2, 1.0f, 0.0f,    0.0f, 0.0f, 1.0f),
		Vertex(-w2, -h2, d2, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f),

		// 正面
		Vertex(-w2, -h2, -d2, 0.0f, 1.0f,   0.0f, 0.0f, -1.0f),
		Vertex(-w2, h2, -d2, 0.0f, 0.0f,    0.0f, 0.0f, -1.0f),
		Vertex(w2, h2, -d2, 1.0f, 0.0f,     0.0f, 0.0f, -1.0f),
		Vertex(w2, -h2, -d2, 1.0f, 1.0f,    0.0f, 0.0f, -1.0f),
	};

	DWORD indexs[] =
	{
		0, 1, 2, 2, 3, 0,		// 右面(+X面)
		4, 5, 6, 6, 7, 4,		// 左面(-X面)
		8, 9, 10, 10, 11, 8,	// 顶面(+Y面)
		12, 13, 14, 14, 15, 12,	// 底面(-Y面)
		16, 17, 18, 18, 19, 16, // 背面(+Z面)
		20, 21, 22, 22, 23, 20	// 正面(-Z面)
	};
	for (size_t i = 0; i < sizeof(v) / sizeof(Vertex); i++)
	{
		v[i].AdjustPosition(offsetx, offsety, offsetz);
		mesh.SetVerTexValue(i, v[i]);
	}
	for (size_t i = 0; i < sizeof(indexs) / sizeof(DWORD); i++)
	{
		mesh.SetIndexValue(i, indexs[i]);
	}
}


void GeometryFactory::CreateDefaultCar(Mesh & mesh)
{

}


