#pragma once
#include "afxwin.h"

class TabTrain : public CDialog
{
	DECLARE_DYNAMIC(TabTrain)

public:
	TabTrain(CWnd* pParent = NULL);
	virtual ~TabTrain();

	enum { IDD = IDD_DIALOG_TRAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö

	DECLARE_MESSAGE_MAP()
public:
	CComboBox TrainArmyStyle;
	CComboBox IsClearArmy;
	CComboBox IsAddArmy;
	CStatic AllCount;
	CEdit Barbarin;
	CEdit Archer;
	CEdit Giant;
	CEdit Goblin;
	CEdit WallBreaker;
	CEdit Ballon;
	CEdit Wizard;
	CEdit Healer;
	CEdit Dragon;
	CEdit Peka;
	CEdit BabyDragon;
	CEdit Miner;
	CEdit Minion;
	CEdit HogRider;
	CEdit Valkyrie;
	CEdit Golem;
	CEdit Witch;
	CEdit LavaHound;
	CEdit BowLer;
	CEdit LightingSpell;
	CEdit HealingSpell;
	CEdit RageSpell;
	CEdit JumpSpell;
	CEdit FreezeSpell;
	CEdit CloneSpell;
	CEdit PoisonSpell;
	CEdit EarthquakeSpell;
	CEdit HasteSpell;
	CEdit SkeletonSpell;
	CEdit InvisibilitySpell;
	CEdit BatSpell;
	// army train speed up
	CButton IsSpeedUp;
	CEdit SpeedUpBegin;
	CEdit SpeedUpEnd;
	CEdit ElectroDragon;
	CEdit Yeti;
	CEdit IceGolem;
	CEdit Headhunter;
private:
	CString m_strLine;
	CPoint m_ptOrigin;
public:
	void TotalInput();
	afx_msg void OnPaint();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnEnChangeEdit14();
	afx_msg void OnEnChangeEdit15();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnEnChangeEdit17();
	afx_msg void OnEnChangeEdit18();
	afx_msg void OnEnChangeEdit19();
	afx_msg void OnEnChangeEdit33();
	afx_msg void OnEnChangeEdit32();
	afx_msg void OnEnChangeEdit34();
	afx_msg void OnEnChangeEdit35();
};
