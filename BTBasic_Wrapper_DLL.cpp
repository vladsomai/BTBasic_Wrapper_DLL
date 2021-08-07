#include "BTBasic_Wrapper_DLL.h"
#include <iostream>
#include <string>
/*
* !!!READ ME!!!!
* 
* DLL MUST BE COMPILED ON X86 ONLY.
* 
* YOU CAN USE GLOBAL VARIABLES - THEY WILL EXIST BETWEEN "dllload" and "dllunload" calls from BTBasic testplan.
* 
* YOU CANNOT DEREFERENCE THE "returnValue" PARAMETER, IT IS AUTOMATICALLY FILLED WITH THE ENUM RETURN TYPE.
*
* DEFAULT "returnValue" FROM "BTBasic_DLL_Call" function is "EXT_DLL_Result::EXT_DLL_Result_Error", 
* RETRUN "EXT_DLL_Result::EXT_DLL_Result_OK" ONLY WHEN YOUR CONDITIONS ARE MET.
* 
* YOU CAN RETURN INFO TO BTBasic TESTPLAN ONLY WITH "returnString", MAXIMUM 2048 BYTES.
* 
* DO NOT CHANGE THE "BTBasic_DLL_Call" FUNCTION SIGNATURE OR REDEFINE THE ENUM "EXT_DLL_Result" FROM THE HEADER.
* 
*/

const bool debugMode = false;

DllExport EXT_DLL_Result BTBasic_DLL_Call(char* functionName, char* parameters,
	char* returnString, int* returnValue)
{
	//Spilt the parameters from BTBasic testplan into an array, similar to UNIX command arguments(argc, argv)
    char* next = parameters;
	char* tokens = strtok_s(parameters, ",", &next);
	int argc = 0;//count number of arguments below
	char* argv[16] = { NULL };//allow max 16 items as parameters
	const char* messageToReturn = nullptr;
	size_t sizeOfMessage{};

	while (tokens != NULL && next != NULL)
	{
		argv[argc] = tokens;
		tokens = strtok_s(next, ",", &next);
		argc++;
	}

	//Handle each function here
	if (strcmp(functionName, "Load") == 0)
	{
		if (true)
		{
			messageToReturn = "Loaded!";
			sizeOfMessage = strlen(messageToReturn) + 1;
			strcpy_s(returnString, sizeOfMessage, messageToReturn);

			return EXT_DLL_Result::EXT_DLL_Result_OK;
		}

		messageToReturn = "Your custom error message for BTBasic.";
		sizeOfMessage = strlen(messageToReturn) + 1;
		strcpy_s(returnString, sizeOfMessage, messageToReturn);

		return EXT_DLL_Result::EXT_DLL_Result_Error;
	}
	else if (strcmp(functionName, "String") == 0)
	{
		std::string stringExample = "String example from C++";

		messageToReturn = stringExample.c_str();
		sizeOfMessage = strlen(messageToReturn) + 1;
		strcpy_s(returnString, sizeOfMessage, messageToReturn);

		return EXT_DLL_Result::EXT_DLL_Result_OK;
	}
	else if (strcmp(functionName, "Parameter_0") == 0)
	{
		if (argv[0] != nullptr)
		{
			messageToReturn = argv[0];
			sizeOfMessage = strlen(messageToReturn) + 1;
			strcpy_s(returnString, sizeOfMessage, messageToReturn);
			return EXT_DLL_Result::EXT_DLL_Result_OK;
		}
		else
		{
			messageToReturn = "Parameter is null.";
			sizeOfMessage = strlen(messageToReturn) + 1;
			strcpy_s(returnString, sizeOfMessage, messageToReturn);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}
	}
	else
	{
		messageToReturn = "Function does not exist!";
		sizeOfMessage = strlen(messageToReturn) + 1;
		strcpy_s(returnString, sizeOfMessage, messageToReturn);

		return EXT_DLL_Result::EXT_DLL_Result_Error;
	}
}