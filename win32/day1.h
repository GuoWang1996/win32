#pragma once
#include "windows.h"
#include "TCHAR.h"
#include "stdio.h"
#include <iostream>
#include "../../DuiLib_Ultimate-master/DuiLib/UIlib.h"
using namespace DuiLib;
#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_d.lib")
#   else
#       pragma comment(lib, "DuiLibA_d.lib") 
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif