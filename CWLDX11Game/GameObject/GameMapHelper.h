#pragma once

#include "GameObjects.h"
#include "../Macro.h"

#include <iostream>
#include <random>


static const int offset = 3;
static const int MazeWidth = 1 + 2 * offset;
static const int BoxWidth = 5.0F;

class GameMapHelper
{
public:
	static bool InitMaze(Microsoft::WRL::ComPtr<ID3D11Device> device, 
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContex, 
		ConstantBuffer<CB_VS_vertexshader>& cb_vs_vertexshader, 
		std::vector<Model*> &objects);

private:
	static void CreateMazeArray(int (*Map)[MazeWidth + 2], int Width);
	static void DfsMazeArray(int(*Map)[MazeWidth + 2], int Width, int x, int y);
};

