#pragma once
#include "../Util/ErrorLogger.h"
#include "WindowContainer.h"

class WindowContainer;

class MainWindow
{
public:
	bool Init(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
	HWND GetHWND() const;
	~MainWindow();
private:
	void RegisterWindowClass();
	HWND m_handle;
	HINSTANCE m_hInstance;
	std::string window_title = "";
	std::wstring window_title_wide = L"";
	std::string window_class = "";
	std::wstring window_class_wide = L"";
	int width = 0;
	int height = 0;
};

