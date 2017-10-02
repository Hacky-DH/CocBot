#pragma once
#ifndef _GLOBAL_H__
#define _GLOBAL_H__
#include "Const.h"
#include "Script.h"
#include "_lua.h"


/*全局变量*/
/*程序运行目录*/
extern CString gcurrent_path;
/*脚本*/
extern  CScript script[MAX_THREAD_COUNT + 1];
/*lua*/
//extern lua_State* glua;
extern _LUA glua[MAX_THREAD_COUNT];


#endif
