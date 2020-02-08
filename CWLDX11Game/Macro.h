#pragma once

#define HR_CHECKER1(hr, str)										\
	if (FAILED(hr))												\
	{															\
		ErrorLogger::Log(hr, str);								\
		return false;											\
	}															