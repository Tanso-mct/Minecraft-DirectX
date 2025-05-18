#pragma once

#define BUILDING_DEVICE_DLL
#ifdef BUILDING_DEVICE_DLL
#define DEVICE_API __declspec(dllexport)
#else
#define DEVICE_API __declspec(dllimport)
#endif