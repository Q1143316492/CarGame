#pragma once
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "../Macro.h"
#include "Mesh.h"
#include "GeometryFactory.h"
#include "Texture.h"

using namespace DirectX;

enum class CollisionType {
	COLLISION_TYPE_UNKNOW,
	COLLISION_TYPE_BOX,
};

class Model
{
public:

	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext, const wchar_t *texturePath, ConstantBuffer<CB_VS_vertexshader> & cb_vs_vertexshader);
	void SetTexture(ID3D11ShaderResourceView * texture);
	void Draw(const XMMATRIX & viewProjectionMatrix);
	virtual void InitializeMesh(Mesh &mesh);

	const XMVECTOR & GetPositionVector() const;
	const XMFLOAT3 & GetPositionFloat3() const;
	const XMVECTOR & GetRotationVector() const;
	const XMFLOAT3 & GetRotationFloat3() const;

	void SetPosition(const XMVECTOR & pos);
	void SetPosition(const XMFLOAT3 & pos);
	void SetPosition(float x, float y, float z);
	void AdjustPosition(const XMVECTOR & pos);
	void AdjustPosition(const XMFLOAT3 & pos);
	void AdjustPosition(float x, float y, float z);
	void SetRotation(const XMVECTOR & rot);
	void SetRotation(const XMFLOAT3 & rot);
	void SetRotation(float x, float y, float z);
	void AdjustRotation(const XMVECTOR & rot);
	void AdjustRotation(const XMFLOAT3 & rot);
	void AdjustRotation(float x, float y, float z);

	const XMVECTOR & GetForwardVector();
	const XMVECTOR & GetRightVector();
	const XMVECTOR & GetBackwardVector();
	const XMVECTOR & GetLeftVector();

	const XMFLOAT3 & GetForwardFloat3();
	const XMFLOAT3 & GetRightFloat3();
	const XMFLOAT3 & GetBackwardFloat3();
	const XMFLOAT3 & GetLeftFloat3();

	CollisionType GetCollisionType();
	void SetCollisionType(CollisionType type);

	virtual float GetCollisionWidthX() { return m_LengthX; }
	virtual float GetCollisionWidthY() { return m_LengthY; }
	virtual float GetCollisionWidthZ() { return m_LengthZ; }

	virtual void InitMatrix();

	virtual void GetCollisionDetection();

	virtual void MoveForward(float speed) {}
	virtual void Movebackward(float speed) {}

	virtual void MoveLeft(float speed) {}
	virtual void MoveRight(float speed) {}

	virtual void TurnLeft(float speed) {}
	virtual void TurnRight(float speed) {}

protected:
	void UpdateWorldMatrix();

protected:
	float m_LengthX = 0.0F;
	float m_LengthY = 0.0F;
	float m_LengthZ = 0.0F;

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	ConstantBuffer<CB_VS_vertexshader> * cb_vs_vertexshader = nullptr;
	ID3D11ShaderResourceView * texture = nullptr;

	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;

	XMMATRIX worldMatrix = XMMatrixIdentity();

	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMFLOAT3 pos;
	XMFLOAT3 rot;

	Mesh m_mesh;

	CollisionType m_CollisionType = CollisionType::COLLISION_TYPE_UNKNOW;

	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_BACKWARD_VECTOR = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR vec_forward;
	XMVECTOR vec_left;
	XMVECTOR vec_right;
	XMVECTOR vec_backward;
};