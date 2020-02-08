#pragma once

#define HR(hr, str)												\
	if (FAILED(hr))												\
	{															\
		ErrorLogger::Log(hr, str);								\
		return false;											\
	}															