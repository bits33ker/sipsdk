#pragma once
#ifdef SIPSDK_STATIC
#define SIPSDK 
#elif defined(SIPSDK_EXPORTS)
#define SIPSDK __declspec(dllexport)
#else
#define SIPSDK __declspec(dllimport)
#endif

