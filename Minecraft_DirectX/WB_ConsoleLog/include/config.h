#pragma once

#define BUILDING_CONSOLE_LOG_DLL
#ifdef BUILDING_CONSOLE_LOG_DLL
#define CONSOLE_LOG_API __declspec(dllexport)
#else
#define CONSOLE_LOG_API __declspec(dllimport)
#endif