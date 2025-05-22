#pragma once

#define BUILDING_GPU_CONTEXT_DLL
#ifdef BUILDING_GPU_CONTEXT_DLL
#define GPU_CONTEXT_API __declspec(dllexport)
#else
#define GPU_CONTEXT_API __declspec(dllimport)
#endif