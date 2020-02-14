#include "ErrorLogger.h"
#include <comdef.h>

void ErrorLogger::Log(std::string message)
{
	std::string error_message = "Error: " + message;
	MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::string message)
{
	_com_error error(hr);
	std::wstring error_message = L"Error: " + StringConverter::StringToWide(message) + L"\n";
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::wstring message)
{
	_com_error error(hr);
	std::wstring error_message = L"Error: " + message + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::ShowMessage(std::string message)
{
	std::string error_message = "Notice: " + message;
	MessageBoxA(NULL, error_message.c_str(), "Notice", MB_SERVICE_NOTIFICATION);
}

void ErrorLogger::ShowMessage(HRESULT hr, std::string message)
{
	_com_error error(hr);
	std::wstring error_message = L"Notice: " + StringConverter::StringToWide(message) + L"\n";
	MessageBoxW(NULL, error_message.c_str(), L"Notice", MB_SERVICE_NOTIFICATION);
}

void ErrorLogger::ShowMessage(HRESULT hr, std::wstring message)
{
	_com_error error(hr);
	std::wstring error_message = L"Notice: " + message + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, error_message.c_str(), L"Notice", MB_SERVICE_NOTIFICATION);
}