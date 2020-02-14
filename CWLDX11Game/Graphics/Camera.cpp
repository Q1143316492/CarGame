#include "Camera.h"

const float Camera::MAX_TPS_ANGLE = MathTools::AngleChange(30.0F);
const float Camera::MIN_TPS_ANGLE = MathTools::AngleChange(-30.0F);

const float Camera::MIN_TPS_LOOKATHEIGHT = 0.0f;
const float Camera::MAX_TPS_LOOKATHEIGHT = 2.0f;

const float Camera::MAX_FPS_LOOKATHEIGHT = 30.0F;
const float Camera::MIN_FPS_LOOKATHEIGHT = -30.0F;

const float Camera::MIN_TPS_DISTANCE = 1.0F;
const float Camera::MAX_TPS_DISTANCE = 10.0F;

Camera::Camera()
{
	this->InitMatrix();
}

void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	float fovRadians = (fovDegrees / 360.0f) * XM_2PI;
	this->projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

const XMMATRIX & Camera::GetViewMatrix() const
{
	return this->viewMatrix;
}

const XMMATRIX & Camera::GetProjectionMatrix() const
{
	return this->projectionMatrix;
}

const XMVECTOR & Camera::GetPositionVector() const
{
	return this->posVector;
}

const XMFLOAT3 & Camera::GetPositionFloat3() const
{
	return this->pos;
}

const XMVECTOR & Camera::GetRotationVector() const
{
	return this->rotVector;
}

const XMFLOAT3 & Camera::GetRotationFloat3() const
{
	return this->rot;
}

void Camera::SetPosition(const XMVECTOR & pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateViewMatrix();
}

void Camera::SetPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMatrix();
}

void Camera::AdjustPosition(const XMVECTOR & pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->UpdateViewMatrix();
}

void Camera::AdjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMatrix();
}

void Camera::SetRotation(const XMVECTOR & rot)
{
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->UpdateViewMatrix();
}

void Camera::SetRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}

void Camera::AdjustRotation(const XMVECTOR & rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->UpdateViewMatrix();
}

void Camera::AdjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}

const XMVECTOR & Camera::GetForwardVector()
{
	return this->vec_forward;
}

const XMVECTOR & Camera::GetRightVector()
{
	return this->vec_right;
}

const XMVECTOR & Camera::GetBackwardVector()
{
	return this->vec_backward;
}

const XMVECTOR & Camera::GetLeftVector()
{
	return this->vec_left;
}

void Camera::InitMatrix()
{
	this->pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->posVector = XMLoadFloat3(&this->pos);
	this->rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}


void Camera::SetLookAtPos(XMFLOAT3 lookAtPos)
{
	XMFLOAT3 VectorLookAt = XMFLOAT3(
		fabs(lookAtPos.x - pos.x), 
		fabs(lookAtPos.y - pos.y), 
		fabs(lookAtPos.z - pos.z));
	float pitch = 0.0f, yaw = 0.0f;
	float dis = sqrt(VectorLookAt.x * VectorLookAt.x + VectorLookAt.z * VectorLookAt.z);
	if (!FLOAT_QEUAL(VectorLookAt.y, 0.0F) && !FLOAT_QEUAL(dis, 0.0F))
	{
		pitch = atan(VectorLookAt.y / sqrt(VectorLookAt.x * VectorLookAt.x + VectorLookAt.z * VectorLookAt.z));
	}
	if (!FLOAT_QEUAL(VectorLookAt.x, 0.0f))
	{
		yaw = atan(VectorLookAt.x / VectorLookAt.z);
	}
	this->SetRotation(pitch, yaw, 0.0f);
}

void Camera::SetLookAtPos(float x, float y, float z)
{
	this->SetLookAtPos(XMFLOAT3(x, y, z));
}

void Camera::SetCameraType(CameraType type)
{
	this->m_cameraType = type;
}

void Camera::UpdateViewMatrix()
{
	if (m_cameraType == CameraType::FIRST_PERSON)
	{
		XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
		XMVECTOR camTarget = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, camRotationMatrix);
		XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, camRotationMatrix);
		camTarget += this->posVector;

		// 修改注视点的高度
		/*XMFLOAT3 tmp;
		DirectX::XMStoreFloat3(&tmp, camTarget);
		tmp.y += this->m_tpsLookAtHeight;
		camTarget = XMLoadFloat3(&tmp);*/

		this->viewMatrix = XMMatrixLookAtLH(this->posVector, camTarget, upDir);
		XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	
		this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
		this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
		this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
		this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
	}
	else
	{
		XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
		XMVECTOR camTarget = this->posVector;
		XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, camRotationMatrix);

		XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
		this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
		this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
		this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
		this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);

		/*
					horizontalLength
				___________  eyes
			    |      .../
		height	|   ../  dis
			    |../
			    goal
		*/
		float height = sin(this->m_tpsYaw) * m_tpsDistance;
		float horizontalLength = cos(this->m_tpsYaw) * m_tpsDistance;
		XMFLOAT3 tpsCameraPos, tmp;
		XMVECTOR tmpVec;
		DirectX::XMStoreFloat3(&tpsCameraPos, this->posVector);
		tpsCameraPos.y += height;
		DirectX::XMStoreFloat3(&tmp, this->vec_backward);
		tpsCameraPos.x += tmp.x;
		tpsCameraPos.z += tmp.z;
		
		tmp = XMFLOAT3(0.0F, m_tpsLookAtHeight, 0.0F);
		tmpVec = XMLoadFloat3(&tmp);
		camTarget += this->vec_forward;
		camTarget += tmpVec;
		this->viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&tpsCameraPos), camTarget, upDir);
	}
}

void Camera::AdjustThirdPersonAngle(float angle)
{
	// todo
	this->m_tpsYaw += angle;
}

void Camera::AdjustThirdPersonDistance(float distance)
{
	this->m_tpsDistance += distance;
	this->m_tpsDistance = std::fmin(m_tpsDistance, Camera::MAX_TPS_DISTANCE);
	this->m_tpsDistance = std::fmax(m_tpsDistance, Camera::MIN_TPS_DISTANCE);
}

void Camera::AdjustFirstPersonLookAtHeight(float height)
{
	this->rot.x = this->rot.x  + height;
	static float mx = 0;
	static float mi = 0;

	this->rot.x = std::fmin(this->rot.x, 1.0F);
	this->rot.x = std::fmax(this->rot.x, -1.0F);
	this->SetRotation(this->rot.x, this->rot.y, this->rot.z);
}

void Camera::AdjustThirdPersonLookAtHeight(float height)
{
	this->m_tpsLookAtHeight -= height;
	this->m_tpsLookAtHeight = std::fmin(m_tpsLookAtHeight, Camera::MAX_TPS_LOOKATHEIGHT);
	this->m_tpsLookAtHeight = std::fmax(m_tpsLookAtHeight, Camera::MIN_TPS_LOOKATHEIGHT);
}

void Camera::MoveForward(float speed)
{
	XMVECTOR vec = this->GetForwardVector() * speed;
	this->AdjustPosition(vec);
}

void Camera::Movebackward(float speed)
{
	XMVECTOR vec = this->GetBackwardVector() * speed;
	this->AdjustPosition(vec);
}

void Camera::MoveLeft(float speed)
{
	XMVECTOR vec = this->GetLeftVector() * speed;
	this->AdjustPosition(vec);
}

void Camera::MoveRight(float speed)
{
	XMVECTOR vec = this->GetRightVector() * speed;
	this->AdjustPosition(vec);
}

void Camera::TurnLeft(float speed)
{
	this->AdjustRotation(0.0F, -speed, 0.0F);
}

void Camera::TurnRight(float speed)
{
	this->AdjustRotation(0.0F, speed, 0.0F);
}
