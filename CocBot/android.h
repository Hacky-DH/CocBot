#pragma once

#ifndef _ANDRIOD_H__
#define _ANDRIOD_H__


/*����adb �� Andriod ����һЩ����*/

#include "pipeshell.h" /*�����ܵ�*/
#include "Const.h"		/*����*/
#include <metrix>
/*����Android ����*/
class Andriod
{
public:
	CString m_adb_name;		/*adb �ļ���*/
private:
	short m_nflag;			/*android ����*/
	short m_android_index;	/*���*/
	CString m_out_put;		/*���*/
	CPipeShell m_pipe;		/*�ܵ�*/
public:/*����*/
	Andriod()
	{
		m_nflag = APP_PLAYER_BLUESTACKS;
	}
	//CString devices()
protected:
private:
};

#endif
