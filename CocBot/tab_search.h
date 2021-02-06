#pragma once
#include "afxwin.h"


// TabSearch 对话框

class TabSearch : public CDialog
{
	DECLARE_DYNAMIC(TabSearch)

public:
	TabSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TabSearch();

// 对话框数据
	enum { IDD = IDD_DIALOG_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit MinTroopRet;
	CButton IsWaitBarbarinKing;
	CButton IsWaitArcherKing;
	// yongwang
	CButton IsWaitGrandKing;
	CButton IsWaitClanCastleTroopsAndSpells;
	CEdit MinTroophs;
	CEdit MaxTroophs;
	CEdit SearchMinGold;
	CEdit SearchMinElixir;
	CEdit SearchMinDarkElixir;
	CComboBox SearchType;
	CComboBox SearchDeadbaseGoldCollector;
	CComboBox SearchDeadbaseElixir;
	CButton ArcherTower;
	CComboBox ArcherTowerLevel;
	CButton Mortar;
	CComboBox MortarLevel;
	CButton WizardTower;
	CComboBox WizardTowerLevel;
	CButton AirDefense;
	CComboBox AirDefenseLevel;
	CButton XBow;
	CComboBox XBowLevel;
	CButton Inferno;
	CComboBox InfernoLevel;
	CButton EagleArtillery;
	CComboBox EagleArtilleryLevel;
	CEdit SearchDelay;
	CEdit SearchWait;
	CEdit SearchMaxCount;
	CButton IsWaitSpell;
	afx_msg void OnPaint();
};
