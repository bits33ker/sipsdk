#pragma once
#ifdef SIPSDK_EXPORTS
#define SIPSDK __declspec(dllexport)
#else
#define SIPSDK __declspec(dllimport)
#endif

