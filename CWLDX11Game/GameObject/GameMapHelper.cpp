#include "GameMapHelper.h"


bool GameMapHelper::InitMaze(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext, ConstantBuffer<CB_VS_vertexshader>& cb_vs_vertexshader, std::vector<Model*>& objects)
{
	// todo 发现bug 动的时候法线没更新，导致光照有问题
	//Box *box = new Box();
	//box->SetBoxLength(5.0F);
	//INIT_MODEL1(!box->Initialize(device, deviceContext, L"Data\\Textures\\wooden.jpg", cb_vs_vertexshader));
	//box->AdjustPosition(0.0f, 0.25f, 5.0f);
	//objects.push_back(box);
	
	int Map[MazeWidth + 2][MazeWidth + 2] = {};
	 GameMapHelper::CreateMazeArray(Map, MazeWidth + 2);
	
	for (int i = 0; i < MazeWidth + 2; i++)
	{
		for (int j = 0; j < MazeWidth + 2; j++)
		{
			if (Map[i][j] == 1) // 在墙的位置放盒子
			{
				Box *box = new Box();
				box->SetBoxLength(BoxWidth);
				INIT_MODEL1(!box->Initialize(device, deviceContext, L"Data\\Textures\\wooden.jpg", cb_vs_vertexshader));
				
				float PosX = (i - offset) * BoxWidth;
				float PosZ = (offset - j) * BoxWidth;
				box->SetPosition(PosX, BoxWidth / 2.0F, PosZ);
				objects.push_back(box);
			}
		}
	}
}

void GameMapHelper::CreateMazeArray(int(*Map)[MazeWidth + 2], int Width)
{
	GameMapHelper::DfsMazeArray(Map, Width, offset + 1, offset + 1);
}

void GameMapHelper::DfsMazeArray(int(*Map)[MazeWidth + 2], int Width, int x, int y)
{
	static int dir[4][2] = { 1, 0, -1, 0, 0, 1, 0, -1 };
	for (int i = 0; i < 4; i++)
	{
		int rnd = rand() % 4;
		std::swap(dir[rnd][0], dir[0][0]); 
		std::swap(dir[rnd][1], dir[0][1]);
	}
	Map[x][y] = 1; // 墙变成路

	//OutputDebugStringA("===============================\n");
	//OutputDebugStringA((std::to_string(x) + std::string(" ") +std::to_string(y) + std::string("\n")).c_str());
	//for (int i = 0; i < Width; i++)
	//{
	//	for (int j = 0; j < Width; j++)
	//	{
	//		OutputDebugStringA((std::to_string(Map[i][j]) + " ").c_str());
	//	}
	//	OutputDebugStringA("\n");
	//}
	//OutputDebugStringA("===============================\n");

	for (int i = 0; i < 4; i++)
	{
		int nextTestX = x + 2 * dir[i][0];
		int nextTextY = y + 2 * dir[i][1];
		if (nextTestX >= 0 && nextTestX < Width && nextTextY >= 0 && nextTextY < Width && Map[nextTestX][nextTextY] == 0)
		{
			int NextStepX = x + dir[i][0];
			int NextStepY = y + dir[i][1];
			Map[NextStepX][NextStepY] = 1; // 墙变成路
			GameMapHelper::DfsMazeArray(Map, Width, nextTestX, nextTextY);
		}
	}

}
