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
	while (!keyboard.CharBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();
	}
	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		CheckGameState(keycode);
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

	while (!keyboard.CharBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();
	}
	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		CheckGameState(keycode);
	}
	while (!mouse.EventBufferIsEmpty())
	{
		MouseEvent me = mouse.ReadEvent();
		if (mouse.IsRightDown())
		{
			if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
			{
				this->gfx.camera.AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);
			}
		}
	}

	if (keyboard.KeyIsPressed('W'))
	{
		this->gfx.car->MoveForward(cameraSpeed);
		this->gfx.camera.SetPosition(gfx.car->GetPositionVector());
		this->gfx.camera.AdjustPosition(0.0F, 1.0F, 0.0F);
	}
	if (keyboard.KeyIsPressed('S'))
	{
		this->gfx.car->Movebackward(cameraSpeed);
		this->gfx.camera.SetPosition(gfx.car->GetPositionVector());
		this->gfx.camera.AdjustPosition(0.0F, 1.0F, 0.0F);
	}
	if (keyboard.KeyIsPressed('A'))
	{
		this->gfx.car->TurnLeft(0.1F); 
		this->gfx.camera.AdjustRotation(0.0F, -0.1F, 0.0F);
	}
	if (keyboard.KeyIsPressed('D'))
	{
		this->gfx.car->TurnRight(0.1F);
		this->gfx.camera.AdjustRotation(0.0F, 0.1F, 0.0F);
	}
}

void Engine::ThirePersonCamera()
{
	const float cameraSpeed = 0.1f;

	while (!keyboard.CharBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();
	}
	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		CheckGameState(keycode);
	}
	while (!mouse.EventBufferIsEmpty())
	{
		MouseEvent me = mouse.ReadEvent();
		if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
		{
			this->gfx.camera.AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);
		}
	}

	if (keyboard.KeyIsPressed('W'))
	{
		this->gfx.car->MoveForward(cameraSpeed);
	}
	if (keyboard.KeyIsPressed('S'))
	{
		this->gfx.car->Movebackward(cameraSpeed);
	}
	if (keyboard.KeyIsPressed('A'))
	{
		//this->gfx.car->MoveLeft(cameraSpeed);
		this->gfx.car->TurnLeft(cameraSpeed);
	}
	if (keyboard.KeyIsPressed('D'))
	{
		//this->gfx.car->MoveRight(cameraSpeed);
		this->gfx.car->TurnRight(cameraSpeed);
	}

	this->gfx.camera.SetPosition(this->gfx.car->GetPositionVector());
	this->gfx.camera.AdjustPosition(0.0F, 2.0F, 0.0F);
	this->gfx.camera.AdjustPosition(this->gfx.car->GetBackwardVector());
}

void Engine::CheckGameState(unsigned char code)
{
	if (code == 0x31)
	{
		gameState = GameState::FIRST_PERSON_FREDOM;
		ErrorLogger::Log("fredom");
		return;
	}
	if (code == 0x32)
	{
		gameState = GameState::FIRST_PERSON_CAMERA;
		ErrorLogger::Log("first person");
		this->gfx.car->InitMatrix();
		this->gfx.camera.InitMatrix();
		this->gfx.car->SetPosition(0.0F, 0.1F, 0.0F);
		this->gfx.camera.SetPosition(0.0F, 1.0F, 0.0F);
		this->gfx.camera.SetLookAtPos(0.0F, 0.0F, 0.5F);
		return;
	}
	if (code == 0x33)
	{
		gameState = GameState::THIRE_PERSON_CAMERA;
		ErrorLogger::Log("third person");
		this->gfx.car->InitMatrix();
		this->gfx.camera.InitMatrix();
		this->gfx.car->SetPosition(0.0F, 0.1F, 0.0F);
		this->gfx.camera.SetPosition(0.0F, 2.0F, -1.0F);
		this->gfx.camera.SetLookAtPos(this->gfx.car->GetPositionFloat3());
		return;
	}
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
