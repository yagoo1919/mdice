#include "CQAPI.h"
#include "common.h"
#define CQEVENT(ReturnType, Name, Size) __pragma(comment(linker, "/EXPORT:" #Name "=_" #Name "@" #Size))\
	extern "C" __declspec(dllexport) ReturnType __stdcall Name
int AuthCode;
CQEVENT(int, Initialize, 4)(const int AuthCode)
{
	::AuthCode = AuthCode;
	return 0;
}
int getAuthCode()
{
	return AuthCode;
}

int cq::getAuthCode()
{
	return AuthCode;
}
