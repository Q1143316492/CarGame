#include "Model.h"

bool Model::Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext, const wchar_t *texturePath, ConstantBuffer<CB_VS_vertexshader>& cb_vs_vertexshader)
{
	HRESULT hr;
	
	hr = DirectX::CreateWICTextureFromFile(device.Get(), texturePath, nullptr, &this->texture);
	HR_CHECKER1(hr, "Failed to create wic texture from file.");

	this->device = device;
	this->deviceContext = deviceContext;
	this->cb_vs_vertexshader = &cb_vs_vertexshader;

	this->InitializeMesh(m_mesh);

	hr = this->vertexBuffer.Initialize(device.Get(), m_mesh.GetVertexArrayAddressOf(), m_mesh.GetVertexSize());
	HR_CHECKER1(hr, "Failed to initialize vertex buffer.");

	hr = this->indexBuffer.Initialize(device.Get(), m_mesh.GetIndexArrayAddressOf(), m_mesh.GetIndexSize());
	HR_CHECKER1(hr, "Failed to initialize index buffer.");

	this->SetPosition(0.0f, 0.0f, 0.0f);
	this->SetRotation(0.0f, 0.0f, 0.0f);
	this->UpdateWorldMatrix();
	return true;
}

void Model::SetTexture(ID3D11ShaderResourceView * texture)
{
	this->texture = texture;
}

void Model::Draw(const XMMATRIX & viewProjectionMatrix)
{
	//Update Constant buffer with WVP Matrix
	this->cb_vs_vertexshader->data.wvpMatrix = this->worldMatrix * viewProjectionMatrix;
	this->cb_vs_vertexshader->data.wvpMatrix = XMMatrixTranspose(this->cb_vs_vertexshader->data.wvpMatrix);
	this->cb_vs_vertexshader->data.worldMatrix = XMMatrixIdentity();
	this->cb_vs_vertexshader->ApplyChanges();
	this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader->GetAddressOf());

	this->deviceContext->PSSetShaderResources(0, 1, &this->texture);
	this->deviceContext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	UINT offset = 0;
	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(), &offset);
	this->deviceContext->DrawIndexed(this->indexBuffer.IndexCount(), 0, 0);
}

void Model::InitializeMesh(Mesh & mesh)
{
	GeometryFactory::CreateBox(mesh, 0.5f, 0.5f, 0.5f);
}

void Model::UpdateWorldMatrix()
{
	this->worldMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z) * XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
}

const XMVECTOR & Model::GetPositionVector() const
{
	return this->posVector;
}

const XMFLOAT3 & Model::GetPositionFloat3() const
{
	return this->pos;
}

const XMVECTOR & Model::GetRotationVector() const
{
	return this->rotVector;
}

const XMFLOAT3 & Model::GetRotationFloat3() const
{
	return this->rot;
}

void Model::SetPosition(const XMVECTOR & pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateWorldMatrix();
}

void Model::SetPosition(const XMFLOAT3 & pos)
{
	this->pos = pos;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void Model::SetPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void Model::AdjustPosition(const XMVECTOR & pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->UpdateWorldMatrix();
}

void Model::AdjustPosition(const XMFLOAT3 & pos)
{
	this->pos.x += pos.y;
	this->pos.y += pos.y;
	this->pos.z += pos.z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void Model::AdjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void Model::SetRotation(const XMVECTOR & rot)
{
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->UpdateWorldMatrix();
}

void Model::SetRotation(const XMFLOAT3 & rot)
{
	this->rot = rot;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void Model::SetRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void Model::AdjustRotation(const XMVECTOR & rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->UpdateWorldMatrix();
}

void Model::AdjustRotation(const XMFLOAT3 & rot)
{
	this->rot.x += rot.x;
	this->rot.y += rot.y;
	this->rot.z += rot.z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void Model::AdjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

const XMVECTOR & Model::GetForwardVector()
{
	return this->vec_forward;
}

const XMVECTOR & Model::GetRightVector()
{
	return this->vec_right;
}

const XMVECTOR & Model::GetBackwardVector()
{
	return this->vec_backward;
}

const XMVECTOR & Model::GetLeftVector()
{
	return this->vec_left;
}