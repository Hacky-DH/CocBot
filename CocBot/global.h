#pragma once
#ifndef _GLOBAL_H__
#define _GLOBAL_H__
#include "Const.h"
#include "Script.h"
#include "_lua.h"


/*ȫ�ֱ���*/
/*��������Ŀ¼*/
extern CString gcurrent_path;
/*�ű�*/
extern  CScript script[MAX_THREAD_COUNT + 1];
/*lua*/
//extern lua_State* glua;
extern _LUA glua[MAX_THREAD_COUNT];


#endif
