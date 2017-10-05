#pragma once
#ifndef _GLOBAL_H__
#define _GLOBAL_H__
#include "Const.h"
#include "Script.h"
#include "_lua.h"


/*全局变量*/

/*脚本*/
extern  CScript script[MAX_THREAD_COUNT + 1];
/*lua 自动管理类*/
extern _LUA glua[MAX_THREAD_COUNT];


#endif
