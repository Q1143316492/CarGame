#pragma once
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh {
public:
	Mesh();
	~Mesh();

	void init(UINT vertexSize, UINT indexSize);
	void SetVerTexValue(UINT index, const Vertex &value);
	void SetIndexValue(UINT index, DWORD value);

	Vertex * GetVertexArrayAddressOf();
	DWORD * GetIndexArrayAddressOf();
	UINT GetVertexSize();
	UINT GetIndexSize();

	Vertex * m_vertexArray;
	DWORD * m_indexArray;
private:
	void InitVertex(UINT vertexSize);
	void InitIndex(UINT indexSize);

	UINT m_vertexArraySize;
	UINT m_indexArraySize;
};

