﻿#pragma once

#define BUILDING_RENDER_DLL
#ifdef BUILDING_RENDER_DLL
#define RENDER_API __declspec(dllexport)
#else
#define RENDER_API __declspec(dllimport)
#endif