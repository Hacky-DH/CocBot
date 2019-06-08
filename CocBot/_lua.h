#pragma once
#ifndef __LUA_H__
#define __LUA_H__

#include <lua.hpp>

class _LUA
{
public:
	_LUA();
	~_LUA();
	/*创建栈*/
	void create_stack();
	/*销毁栈*/
	void close_stack();
	/*设置编号,全局只需设置一次*/
	void set_index(int index);
	/*调用脚本*/
	int call_script(CString script_name);
private:
	/*初始化，注册函数*/
	void init();
protected:
	/*lua 栈 指针*/
	lua_State* m_lua_state;
	/*设置全局编号*/
	int m_index;
private:
};

typedef _LUA CLua;
typedef _LUA* LPlua;

#endif
