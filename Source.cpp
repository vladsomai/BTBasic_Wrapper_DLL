#include <iostream>
#include "BTBasic_Wrapper_DLL.h"

int main()
{
	{
		char functionName[100] = "Load";
		char Parameters[100] = "00";
		char returnString[2028] = "";
		int* returnVal = nullptr;
		uint16_t a = 0;

		EXT_DLL_Result result = BTBasic_DLL_Call(functionName, Parameters, returnString, returnVal);
		std::cout << "Return string: " << returnString << std::endl;
	}
}