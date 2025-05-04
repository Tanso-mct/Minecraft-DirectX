#pragma once

#define BUILDING_CONTAINER_DLL
#ifdef BUILDING_CONTAINER_DLL
#define CONTAINER_API __declspec(dllexport)
#else
#define CONTAINER_API __declspec(dllimport)
#endif