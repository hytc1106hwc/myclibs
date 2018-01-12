#pragma once

#ifdef MYCLIBS_EXPORTS
	#include "lua.hpp"
	#include <stdarg.h>
	#include <stdlib.h>
	#include <string.h>
#else
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
#endif // MYCLIBS_EXPORTS

#define LUA_BUILD_AS_DLL
#if defined (LUA_BUILD_AS_DLL)
	#ifdef MYCLIBS_EXPORTS
		#define MYCLIBS_API __declspec(dllexport)
	#else
		#define MYCLIBS_API __declspec(dllimport)
	#endif // MYCLIBS_EXPORTS
#else
	#define MYCLIBS_API extern
#endif // (LUA_BUILD_AS_DLL)
