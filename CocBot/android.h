#pragma once

#ifndef _ANDRIOD_H__
#define _ANDRIOD_H__


/*利用adb 对 Andriod 进行一些操作*/

#include "pipeshell.h" /*匿名管道*/
#include "Const.h"		/*常量*/
#include <metrix>
/*常用Android 命令*/
class Andriod
{
public:
	CString m_adb_name;		/*adb 文件名*/
private:
	short m_nflag;			/*android 类型*/
	short m_android_index;	/*编号*/
	CString m_out_put;		/*输出*/
	CPipeShell m_pipe;		/*管道*/
public:/*方法*/
	Andriod()
	{
		m_nflag = APP_PLAYER_BLUESTACKS;
	}
	//CString devices()
protected:
private:
};

#endif
