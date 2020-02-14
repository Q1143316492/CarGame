#pragma once

#include "WindowContainer.h"
#include "Macro.h"
#include "GameObject/GameObjects.h"
#include <iostream>

class Engine : WindowContainer
{
public:
	enum class GameState {
		FIRST_PERSON_FREDOM,
		FIRST_PERSON_CAMERA,
		THIRE_PERSON_CAMERA
	};
	
	bool Init(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();

	void FirstPersonFredom();
	void FirstPersonCamera();
	void ThirePersonCamera();
	bool CheckGameState(unsigned char code);

	void Update();

	void RenderFrame();
private:
	GameState gameState = GameState::FIRST_PERSON_FREDOM;
};

