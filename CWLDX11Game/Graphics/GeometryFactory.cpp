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

void GeometryFactory::CreateCylinder(Mesh & mesh, float radius, float height, float level)
{

	std::vector<Vertex> v;
	std::vector<DWORD> indexs;

	float offset = 360 / level;
	float pindex = 0;

	v.push_back(Vertex(0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F));
	pindex++;

	for (int i = 0; i < 360; i += offset)
	{
		float x = radius * cos(MathTools::AngleChange(i));
		float z = radius * sin(MathTools::AngleChange(i));

		float nx = radius * cos(MathTools::AngleChange(i + offset));
		float nz = radius * sin(MathTools::AngleChange(i + offset));
		v.push_back(Vertex(nx, height / 2.0F, nz, 0.0F, 1.0F, 0.0F, 1.0F, 0.0F));	// [1] pindex - 4
		v.push_back(Vertex(x, height / 2.0F, z, 1.0F, 0.0F, 0.0F, 1.0F, 0.0F));	    // [2] pindex - 3
		indexs.push_back(0);
		indexs.push_back(pindex++);
		indexs.push_back(pindex++);

		v.push_back(Vertex(x, -height / 2.0F, z, 1.0F, 0.0F, 0.0F, 1.0F, 0.0F));    // [4] pindex - 2
		v.push_back(Vertex(nx, -height / 2.0F, nz, 0.0F, 1.0F, 0.0F, 1.0F, 0.0F));  // [3] pindex - 1
		indexs.push_back(pindex++);
		indexs.push_back(pindex++);
		indexs.push_back(0);

		// [4 2 1]
		indexs.push_back(pindex - 2);
		indexs.push_back(pindex - 3);
		indexs.push_back(pindex - 4);

		// [1 3 4]
		indexs.push_back(pindex - 4);
		indexs.push_back(pindex - 1);
		indexs.push_back(pindex - 2);
	}
	mesh.init(v.size(), indexs.size());
	for (size_t i = 0; i < v.size(); i++)
	{
		mesh.SetVerTexValue(i, v[i]);
	}
	for (size_t i = 0; i < indexs.size(); i++)
	{
		mesh.SetIndexValue(i, indexs[i]);
	}

}

void GeometryFactory::Test(Mesh & mesh)
{
	mesh.init(3, 3);
	float w2 = 5.0F / 2, h2 = 5.0F / 2, d2 = 5.0F / 2;

	std::vector<Vertex> v;
	//v.push_back(Vertex(w2, -h2, -d2, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f));
	//v.push_back(Vertex(w2, h2, -d2, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
	//v.push_back(Vertex(w2, h2, d2, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f));

	v.push_back(Vertex(0.0F, 0.0F, 0.0F, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	v.push_back(Vertex(4.7F, 0.0F, 1.5F, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));
	v.push_back(Vertex(5.0F, 0.0F, 0.0F, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f));

	std::vector<DWORD> indexs;
	indexs.push_back(0);
	indexs.push_back(1);
	indexs.push_back(2);


	for (size_t i = 0; i < v.size(); i++)
	{
		mesh.SetVerTexValue(i, v[i]);
	}
	for (size_t i = 0; i < indexs.size(); i++)
	{
		mesh.SetIndexValue(i, indexs[i]);
	}
}


