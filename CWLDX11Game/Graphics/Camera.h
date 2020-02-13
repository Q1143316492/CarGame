#pragma once

#include <DirectXMath.h>

#include "../Macro.h"
#include "../Util/MathTools.h"

using namespace DirectX;

class Camera
{
public:
	Camera();

	static enum class CameraType {
		FIRST_PERSON,
		THIRD_PERSON,
	};

	void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);

	const XMMATRIX & GetViewMatrix() const;
	const XMMATRIX & GetProjectionMatrix() const;

	const XMVECTOR & GetPositionVector() const;
	const XMFLOAT3 & GetPositionFloat3() const;
	const XMVECTOR & GetRotationVector() const;
	const XMFLOAT3 & GetRotationFloat3() const;

	void SetPosition(const XMVECTOR & pos);
	void SetPosition(float x, float y, float z);
	void AdjustPosition(const XMVECTOR & pos);
	void AdjustPosition(float x, float y, float z);

	void SetRotation(const XMVECTOR & rot);
	void SetRotation(float x, float y, float z);
	void AdjustRotation(const XMVECTOR & rot);
	void AdjustRotation(float x, float y, float z);

	void SetLookAtPos(XMFLOAT3 lookAtPos);
	void SetLookAtPos(float x, float y, float z);

	void SetCameraType(CameraType type);

	const XMVECTOR & GetForwardVector();
	const XMVECTOR & GetRightVector();
	const XMVECTOR & GetBackwardVector();
	const XMVECTOR & GetLeftVector();

	void InitMatrix();

	virtual void MoveForward(float speed);
	virtual void Movebackward(float speed);
	virtual void MoveLeft(float speed);
	virtual void MoveRight(float speed);

	void TurnLeft(float speed);
	void TurnRight(float speed);

	void AdjustThirdPersonAngle(float angle);
	void AdjustThirdPersonDistance(float distance);
	void AdjustThirdPersonLookAtHeight(float height);
private:
	void UpdateViewMatrix();

private:
	XMVECTOR posVector;
	XMVECTOR rotVector;
	
	XMFLOAT3 pos;
	XMFLOAT3 rot;

	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_BACKWARD_VECTOR = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR vec_forward;
	XMVECTOR vec_left;
	XMVECTOR vec_right;
	XMVECTOR vec_backward;

	CameraType m_cameraType = CameraType::FIRST_PERSON;

	static const float MIN_TPS_ANGLE;
	static const float MAX_TPS_ANGLE;

	float m_tpsYaw = MathTools::AngleChange(30.0F);
	
	static const float MAX_TPS_DISTANCE;
	static const float MIN_TPS_DISTANCE;
	
	static const float MIN_TPS_LOOKATHEIGHT;
	static const float MAX_TPS_LOOKATHEIGHT;

	float m_tpsDistance = 2.0F; // 第三人称视角 物体到相机的距离
	float m_tpsLookAtHeight = 0.0F;
};