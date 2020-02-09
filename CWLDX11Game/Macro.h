#pragma once

#define FLOAT_QEUAL(a, b) (fabs(a - b) < 1e-6)

#define INIT_MODEL1(Boolean)							        \
	if (Boolean)												\
	{															\
		return false;											\
	}	

#define INIT_MODEL2(Boolean, str)							    \
	if (Boolean)												\
	{															\
		ErrorLogger::Log(str);								    \
		return false;											\
	}	

#define HR_CHECKER1(hr, str)									\
	if (FAILED(hr))												\
	{															\
		ErrorLogger::Log(hr, str);								\
		return false;											\
	}					


#define HR_CHECKER2(hr, str)									\
	if (FAILED(hr))												\
	{															\
		ErrorLogger::Log(hr, str);								\
	}	