#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// TabStats 对话框

class TabStats : public CDialog
{
	DECLARE_DYNAMIC(TabStats)

public:
	TabStats(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TabStats();

// 对话框数据
	enum { IDD = IDD_DIALOG_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl1;
	CStatic RunTime;
	CStatic AttackCount;
	CStatic SearchCount;
	CStatic m_ThreadCount;
	afx_msg void OnPaint();
};
