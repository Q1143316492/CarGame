#include "Mesh.h"

Mesh::Mesh()
	: m_vertexArray(nullptr),
	m_indexArray(nullptr)
{
}

Mesh::~Mesh()
{
	delete[] m_vertexArray;
	delete[] m_indexArray;
}

void Mesh::init(UINT vertexSize, UINT indexSize)
{
	InitVertex(vertexSize);
	InitIndex(indexSize);
}

void Mesh::SetVerTexValue(UINT index, const Vertex &value)
{
	if (index >= 0 && index < this->GetVertexSize())
	{
		this->m_vertexArray[index].pos = value.pos;
		this->m_vertexArray[index].texCoord = value.texCoord;
		this->m_vertexArray[index].normal = value.normal;
	}
}

void Mesh::SetIndexValue(UINT index, DWORD value)
{
	if (index >= 0 && index < this->GetIndexSize())
	{
		this->m_indexArray[index] = value;
	}
}

Vertex * Mesh::GetVertexArrayAddressOf()
{
	return this->m_vertexArray;
}

DWORD * Mesh::GetIndexArrayAddressOf()
{
	return this->m_indexArray;
}

void Mesh::InitVertex(UINT vertexSize)
{
	delete[] m_vertexArray;
	this->m_vertexArraySize = vertexSize;
	m_vertexArray = new Vertex[vertexSize];
}

void Mesh::InitIndex(UINT indexSize)
{
	delete[] m_indexArray;
	this->m_indexArraySize = indexSize;
	m_indexArray = new DWORD[indexSize];
}

UINT Mesh::GetVertexSize()
{
	return this->m_vertexArraySize;
}

UINT Mesh::GetIndexSize()
{
	return this->m_indexArraySize;
}
