// MyClibs.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "myclibs.h"

#define MYCLIBS_NAME "myclibs"
using namespace std;

MYCLIBS_API void error(lua_State *L, const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}

MYCLIBS_API bool myclibs_checkrange(lua_State *L, double r)
{
	if (r <= MININT32 || r >= MAXINT32)
	{
		error(L, "result should between %d and %d", MININT32, MAXINT32);
	}
	return true;
}

/* summation of multi values */
MYCLIBS_API int myclibs_summation(lua_State *L)
{
	int i;
	int top = lua_gettop(L);
	double result = 0;
	if (top == 0)
	{
		lua_pushnumber(L, result);
	}
	else 
	{
		for (i = 1; i <= top; i++)
		{
			int t = lua_type(L, i);
			switch (t)
			{
				case LUA_TNUMBER:
				{
					myclibs_checkrange(L, result);	/* check value */
					result += (double)lua_tonumber(L, i);
					lua_pushnumber(L, result);
					break;
				}
				default:
				{
					const char *tyname = lua_typename(L, t);
					error(L, "bad argument #%d to 'summation'(number expected, got %s", i, tyname);
					break;
				}
			}
		}
	}
	return 1;
}

/* subversion of multi values */
MYCLIBS_API int myclibs_subversion(lua_State *L)
{
	int i;
	int top = lua_gettop(L);
	double result = 0;
	if (top == 0)
	{
		lua_pushnumber(L, result);
	}
	else
	{
		for (i = 1; i <= top; i++) {
			int t = lua_type(L, i);
			switch (t)
			{
				case LUA_TNUMBER:
				{
					myclibs_checkrange(L, result); /* check value */
					result -= (double)lua_tonumber(L, i);
					lua_pushnumber(L, result);
					break;
				}
				default:
				{
					const char *tyname = lua_typename(L, t);
					error(L, "bad argument #%d to 'summation'(number expected, got %s", i, tyname);
					break;
				}
			}
		}
	}
	return 1;
}

/* define functions to be registered */
static const luaL_Reg myclibs[] = {
	{ "sum", myclibs_summation },
	{ "sub", myclibs_subversion },
	{ NULL, NULL }
};

/* create a new lib and set an alias for the lib */
MYCLIBS_API int luaopen_myclibs(lua_State *L)
{
	luaL_newlib(L, myclibs);
	lua_setglobal(L, MYCLIBS_NAME);
	return 1;
}