#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// TabQuickSet 对话框

class TabQuickSet : public CDialogEx
{
	DECLARE_DYNAMIC(TabQuickSet)

public:
	TabQuickSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TabQuickSet();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	// 游戏区服
	CComboBox GameVersion;
	CButton OffLine;
	CButton RequestArmy;
	CButton Attack;
	CButton DonateArmy;
	CButton UpgradeWall;
	CButton UpgradeHeros;
	CButton ControlTroophs;
	CButton LightingDarkElixir;
	CButton RemoveTree;
	CButton RearmAll;
	CEdit LoadOutSet;
	
	
	afx_msg void OnBsOrOtherChange();
	afx_msg void OnLoadInConfig();
	afx_msg void OnLoadOutConfig();
	CEdit LoadInSet;
	afx_msg void OnSelectFile();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtQuickset();
	HWND hParent;//父窗口句柄
	CComboBox townLevel;
	CButton check_bs;
	afx_msg void OnBnClickedCheckBs();
	afx_msg void OnBnClickedCheckLd();
	BOOL app_player_type;
	CListBox m_list;
};
