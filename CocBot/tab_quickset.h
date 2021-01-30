#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


class TabQuickSet : public CDialogEx
{
	DECLARE_DYNAMIC(TabQuickSet)

public:
	TabQuickSet(CWnd* pParent = NULL);
	virtual ~TabQuickSet();

	enum { IDD = IDD_DIALOG_QUICKSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

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
