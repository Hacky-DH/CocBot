#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// TabStats �Ի���

class TabStats : public CDialog
{
	DECLARE_DYNAMIC(TabStats)

public:
	TabStats(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TabStats();

// �Ի�������
	enum { IDD = IDD_DIALOG_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl1;
	CStatic RunTime;
	CStatic AttackCount;
	CStatic SearchCount;
	CStatic m_ThreadCount;
	afx_msg void OnPaint();
};
