#pragma once
#ifndef _GLOBAL_H__
#define _GLOBAL_H__
#include "Const.h"
#include "Script.h"
#include "_lua.h"


/*ȫ�ֱ���*/

/*�ű�*/
extern  CScript script[MAX_THREAD_COUNT + 1];
/*lua �Զ�������*/
extern _LUA glua[MAX_THREAD_COUNT];


#endif
