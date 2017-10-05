#pragma once
#ifndef __LUA_H__
#define __LUA_H__
#ifdef _DEBUG
#pragma comment(lib,"Debug/lua5.3.lib")
#else
#pragma comment(lib,"Release/lua5.3.lib")
#endif // _DEBUG

extern "C"
{
#include <lua.h>			/*lua*/
#include <lualib.h>			/*lua*/
#include <lauxlib.h>		/*lua*/
}
class _LUA
{
public:
	_LUA();
	~_LUA();
	/*����ջ*/
	void create_stack();
	/*����ջ*/
	void close_stack();
	/*���ñ��,ȫ��ֻ������һ��*/
	void set_index(int index);
	/*���ýű�*/
	int call_script(CString script_name);
private:
	/*��ʼ����ע�ắ��*/
	void init();
protected:
	/*lua ջ ָ��*/
	lua_State* m_lua_state;
	/*����ȫ�ֱ��*/
	int m_index;
private:
};

typedef _LUA CLua;
typedef _LUA* LPlua;

#endif
