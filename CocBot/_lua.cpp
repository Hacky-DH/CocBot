#include "stdafx.h"
#include "_lua.h"
#include "lua_func.h"
_LUA:: _LUA()
{
	m_lua_state = luaL_newstate();
	if (m_lua_state == nullptr)exit(-1);
	luaL_openlibs(m_lua_state);/*加载基本库*/
	luaopen_base(m_lua_state);
	luaopen_table(m_lua_state);
	luaopen_string(m_lua_state);
	luaopen_math(m_lua_state);
#ifdef _DEBUG
	luaopen_debug(m_lua_state);
#endif
	m_index = 0;
	init();
}

_LUA::~_LUA()
{
	if (m_lua_state)lua_close(m_lua_state);
	m_lua_state = NULL;
}

void _LUA::create_stack()
{
	if (m_lua_state)
		lua_close(m_lua_state);
	m_lua_state = luaL_newstate();
	if (m_lua_state == nullptr)exit(-1);
	luaL_openlibs(m_lua_state);/*加载基本库*/
	luaopen_base(m_lua_state);
	luaopen_table(m_lua_state);
	luaopen_string(m_lua_state);
	luaopen_math(m_lua_state);
#ifdef _DEBUG
	luaopen_debug(m_lua_state);
#endif
	m_index = 0;
	init();
}

void _LUA::close_stack()
{
	if (m_lua_state)lua_close(m_lua_state);
	m_lua_state = NULL;
}


int _LUA::call_script(CString script_name)
{
	if (script_name.Find("\\") <= 0)/*判断是否为绝对路径*/
		script_name = GetCurrentPath() + "Function\\Lua\\" + script_name;
	if (luaL_loadfile(m_lua_state, script_name) != 0)
	{
		//lua
		script[m_index].SetLog("加载文件失败！");
		return -1;
	}
	if (lua_pcall(m_lua_state, 0, 0, 0) != 0)
	{
		script[m_index].SetLog("call lua false");
		return -2;
	}
	return 0;
}

void _LUA::init()
{
	lua_register(m_lua_state, "SetLog", SetLog);
	lua_register(m_lua_state, "GetColor", GetColor);
	lua_register(m_lua_state, "Tap", Tap);
	lua_register(m_lua_state, "FindColor", FindColor);
	lua_register(m_lua_state, "FindColorEx", FindColorEx);
	lua_register(m_lua_state, "FindMultiColor", FindMultiColor);
	lua_register(m_lua_state, "FindMultiColorEx", FindMultiColorEx);
	lua_register(m_lua_state, "FindPic", FindPic);
	lua_register(m_lua_state, "FindPicEx", FindPicEx);
	lua_register(m_lua_state, "SetPath", SetPath);
	lua_register(m_lua_state, "Dealy", Dealy);
	lua_register(m_lua_state, "SelectSolider", SelectSolider);
	lua_register(m_lua_state, "GetAttackPos", GetAttackPos);
	lua_register(m_lua_state, "GetAttackPosEx", GetAttackPosEx);
	lua_register(m_lua_state, "SelectSpell", SelectSpell);
	lua_register(m_lua_state, "SelectHero", SelectHero);
	
}

void _LUA::set_index(int index)
{
	m_index = index<0 || index>MAX_THREAD_COUNT ? 0 : index;
	lua_pushnumber(m_lua_state, m_index);
	lua_setglobal(m_lua_state, "g_app_player_index");
}