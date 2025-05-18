#pragma once

#define BUILDING_WINDOW_CONTEXT_DLL
#ifdef BUILDING_WINDOW_CONTEXT_DLL
#define WINDOW_CONTEXT_API __declspec(dllexport)
#else
#define WINDOW_CONTEXT_API __declspec(dllimport)
#endif