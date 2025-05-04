#pragma once

#define BUILDING_UTILITY_DLL
#ifdef BUILDING_UTILITY_DLL
#define UTILITY_API __declspec(dllexport)
#else
#define UTILITY_API __declspec(dllimport)
#endif