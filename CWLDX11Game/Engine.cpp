#include "Engine.h"

bool Engine::Init(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{

	if (!this->window.Init(this, hInstance, window_title, window_class, width, height))
		return false;

	if (!this->gfx.Init(window.GetHWND(), width, height))
		return false;
}

bool Engine::ProcessMessages()
{
	return this->window.ProcessMessages();
}

void Engine::FirstPersonFredom()
{
	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		if (CheckGameState(keycode))
		{
			return;
		}
	}
	while (!mouse.EventBufferIsEmpty())
	{
		MouseEvent me = mouse.ReadEvent();
		if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
		{
			this->gfx.camera.AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);
		}
	}

	const float cameraSpeed = 0.1f;

	if (keyboard.KeyIsPressed('W'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetForwardVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed('S'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetBackwardVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed('A'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetLeftVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed('D'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetRightVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed(VK_SPACE))
	{
		this->gfx.camera.AdjustPosition(0.0f, cameraSpeed, 0.0f);
	}
	if (keyboard.KeyIsPressed(VK_CONTROL))
	{
		this->gfx.camera.AdjustPosition(0.0f, -cameraSpeed, 0.0f);
	}
}

void Engine::FirstPersonCamera()
{
	const float cameraSpeed = 0.1f;

	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		if (CheckGameState(keycode))
		{
			return;
		}
	}
	while (!mouse.EventBufferIsEmpty())
	{
		MouseEvent me = mouse.ReadEvent();
		if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
		{
			this->gfx.camera.AdjustRotation(0.0F, (float)me.GetPosX() * 0.01f, 0.0F);
			this->gfx.camera.AdjustFirstPersonLookAtHeight((float)me.GetPosY() * 0.01);
			
		}
	}

	float tyreRot = 0;	// 轮子左右转向旋转
	float tyreRotForward = 0;	// 轮子是否旋转

	if (keyboard.KeyIsPressed('W'))
	{
		this->gfx.car.MoveForward(cameraSpeed);
		this->gfx.camera.SetPosition(gfx.car.GetPositionVector());
		this->gfx.camera.AdjustPosition(0.0F, 1.0F, 0.0F);
		tyreRotForward = 10;
	}
	if (keyboard.KeyIsPressed('S'))
	{
		this->gfx.car.Movebackward(cameraSpeed);
		this->gfx.camera.SetPosition(gfx.car.GetPositionVector());
		this->gfx.camera.AdjustPosition(0.0F, 1.0F, 0.0F);
		tyreRotForward = -10;
	}
	if (keyboard.KeyIsPressed('A'))
	{
		this->gfx.car.TurnLeft(0.1F); 
		this->gfx.camera.AdjustRotation(0.0F, -0.1F, 0.0F);
		tyreRot -= 0.1F;
	}
	if (keyboard.KeyIsPressed('D'))
	{
		this->gfx.car.TurnRight(0.1F);
		this->gfx.camera.AdjustRotation(0.0F, 0.1F, 0.0F);
		tyreRot = 0.1F;
	}

	this->gfx.sky.MoveSkyBox(&this->gfx.car);

	// 轮子跟随车子
	std::vector<XMFLOAT3> vecTyresPosition;
	std::vector<XMFLOAT3> vecTyresRotation;
	this->gfx.car.CalculateTyresPosition(vecTyresPosition);
	this->gfx.car.CalculateTyresRotation(vecTyresRotation, tyreRotForward, tyreRot);
	for (int i = 0; i < 4; i++)
	{
		this->gfx.tyres[i]->SetRotation(vecTyresRotation[i]);
		this->gfx.tyres[i]->SetPosition(vecTyresPosition[i]);
	}

}

void Engine::ThirePersonCamera()
{
	const float cameraSpeed = 0.1f;
	static float disCamera = 2.0F;
	static float rot = 0.0F;

	while (!keyboard.CharBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();
	}
	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		if (CheckGameState(keycode))
		{
			return;
		}
	}
	while (!mouse.EventBufferIsEmpty())
	{
		MouseEvent me = mouse.ReadEvent();
		if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
		{
			this->gfx.camera.AdjustRotation(0, (float)me.GetPosX() * 0.01f, 0);
			this->gfx.camera.AdjustThirdPersonLookAtHeight((float)me.GetPosY() * 0.01f);
		}
		if (me.GetType() == MouseEvent::EventType::WheelUp)
		{
			this->gfx.camera.AdjustThirdPersonDistance(-0.1F);
		}
		if (me.GetType() == MouseEvent::EventType::WheelDown)
		{
			this->gfx.camera.AdjustThirdPersonDistance(0.1F);
		}
	}

	float tyreRot = 0;	// 轮子左右转向旋转
	float tyreRotForward = 0;	// 轮子是否旋转
	if (keyboard.KeyIsPressed('W'))
	{
		this->gfx.car.MoveForward(cameraSpeed);
		tyreRotForward = 10;
	}
	if (keyboard.KeyIsPressed('S'))
	{
		this->gfx.car.Movebackward(cameraSpeed);		
		tyreRotForward = -10;
	}
	if (keyboard.KeyIsPressed('A'))
	{
		this->gfx.car.TurnLeft(cameraSpeed);
		tyreRot -= 0.1F;
	}
	if (keyboard.KeyIsPressed('D'))
	{
		this->gfx.car.TurnRight(cameraSpeed);
		tyreRot += 0.1F;
	}
	this->gfx.camera.SetPosition(this->gfx.car.GetPositionVector());

	// 天空盒子跟随
	this->gfx.sky.MoveSkyBox(&this->gfx.car);
	// 轮子跟随
	std::vector<XMFLOAT3> vecTyresPosition;
	std::vector<XMFLOAT3> vecTyresRotation;
	this->gfx.car.CalculateTyresPosition(vecTyresPosition);
	this->gfx.car.CalculateTyresRotation(vecTyresRotation, tyreRotForward, tyreRot);
	for (int i = 0; i < 4; i++)
	{
		this->gfx.tyres[i]->SetRotation(vecTyresRotation[i]);
		this->gfx.tyres[i]->SetPosition(vecTyresPosition[i]);
	}
}

bool Engine::CheckGameState(unsigned char code)
{
	if (code == 0x31)
	{
		gameState = GameState::FIRST_PERSON_FREDOM;
		this->gfx.camera.SetCameraType(Camera::CameraType::FIRST_PERSON);
		this->FirstPersonFredom();
		ErrorLogger::ShowMessage("fredom mode");
		return true;
	}
	if (code == 0x32)
	{
		gameState = GameState::FIRST_PERSON_CAMERA;
		this->gfx.camera.SetCameraType(Camera::CameraType::FIRST_PERSON);
		
		this->gfx.car.InitMatrix();
		this->gfx.car.SetPosition(0.0F, 0.25F, 0.0F);

		this->gfx.camera.InitMatrix();
		this->gfx.camera.SetPosition(gfx.car.GetPositionVector());
		this->gfx.camera.AdjustPosition(0.0F, 2.0F, 0.0F);

		this->FirstPersonCamera();
		ErrorLogger::ShowMessage("first person game mode");
		return true;
	}
	if (code == 0x33)
	{
		gameState = GameState::THIRE_PERSON_CAMERA;
		this->gfx.camera.SetCameraType(Camera::CameraType::THIRD_PERSON);
		ErrorLogger::ShowMessage("third person game mode");

		this->gfx.car.InitMatrix();
		this->gfx.car.SetPosition(0.0F, 0.25F, 0.0F);

		this->gfx.camera.InitMatrix();
		this->gfx.camera.SetPosition(0.0F, 2.0F, 0.0F);
		this->gfx.camera.SetLookAtPos(this->gfx.car.GetPositionFloat3());
		this->ThirePersonCamera();
		return true;
	}
	return false;
}

void Engine::Update()
{
	if (this->gameState == GameState::FIRST_PERSON_FREDOM)
	{
		this->FirstPersonFredom();
	}
	else if (this->gameState == GameState::FIRST_PERSON_CAMERA)
	{
		this->FirstPersonCamera();
	}
	else if (this->gameState == GameState::THIRE_PERSON_CAMERA)
	{
		this->ThirePersonCamera();
	}
}

void Engine::RenderFrame()
{
	gfx.RenderFrame();
}
