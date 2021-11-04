/*
* !!!READ ME!!!!
* 
* DLL MUST BE COMPILED ON X86 ONLY.
* 
* YOU CAN USE GLOBAL VARIABLES - THEY WILL EXIST BETWEEN "dllload" and "dllunload" calls from BTBasic testplan.
* 
* YOU CANNOT DEREFERENCE THE "returnValue" PARAMETER, IT IS SET ONLY BY THE BTBasic HOST PROCESS WITH THE ENUM RETURN TYPE.
* The "returnValue" can be used from MCD only.
*
* DEFAULT "returnValue" FROM "BTBasic_DLL_Call" function is "EXT_DLL_Result::EXT_DLL_Result_Error", 
* RETRUN "EXT_DLL_Result::EXT_DLL_Result_OK" ONLY WHEN YOUR CONDITIONS ARE MET.
* 
* YOU CAN RETURN INFO TO BTBasic TESTPLAN ONLY WITH "returnString", MAXIMUM 2048 BYTES.
* 
* DO NOT CHANGE THE "BTBasic_DLL_Call" FUNCTION SIGNATURE OR REDEFINE / MODIFY THE ENUM "EXT_DLL_Result" FROM THE HEADER.
* 
*/
#include "lib.h"
#include "BTBasic_Wrapper_DLL.h"

extern void copyReturnString(const char* input, char* retString);
extern std::vector<std::string> parse_C_style_str(char* input);

DllExport EXT_DLL_Result BTBasic_DLL_Call(char* functionName, char* parameters,
	char* returnString, int* returnValue)
{
	const char* messageToReturn = nullptr;
	size_t sizeOfMessage{};

	std::vector<std::string> params = parse_C_style_str(parameters);

	//Handle each function here
	if (strcmp(functionName, "FirstParameter") == 0)
	{
		copyReturnString(params.at(0).c_str(), returnString);
		return EXT_DLL_Result::EXT_DLL_Result_OK;
	}
	else if (strcmp(functionName, "Test") == 0)
	{
		copyReturnString("Test function executed", returnString);
		return EXT_DLL_Result::EXT_DLL_Result_OK;
	}
	else
	{
		copyReturnString("Function does not exist!", returnString);
		return EXT_DLL_Result::EXT_DLL_Result_Error;
	}

	/*
	* DO NOT REMOVE
	* Function should not reach this state
	* Secure the return of the function in case programmer messes with the if block above
	*/
	copyReturnString("Default return state reached, please chack the wrapper DLL return paths", returnString);
	return EXT_DLL_Result::EXT_DLL_Result_Error;
}

