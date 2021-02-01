// TabTrain.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "tab_train.h"
#include "afxdialogex.h"


// TabTrain 对话框

IMPLEMENT_DYNAMIC(TabTrain, CDialog)

TabTrain::TabTrain(CWnd* pParent /*=NULL*/)
	: CDialog(TabTrain::IDD, pParent)
	,m_strLine(_T(""))
	,m_ptOrigin(0)
{

}

TabTrain::~TabTrain()
{
}

void TabTrain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, TrainArmyStyle);
	DDX_Control(pDX, IDC_COMBO2, IsClearArmy);
	DDX_Control(pDX, IDC_COMBO3, IsAddArmy);
	DDX_Control(pDX, IDC_EDIT1, Barbarin);
	DDX_Control(pDX, IDC_EDIT2, Archer);
	DDX_Control(pDX, IDC_EDIT3, Giant);
	DDX_Control(pDX, IDC_EDIT4, Goblin);
	DDX_Control(pDX, IDC_EDIT5, WallBreaker);
	DDX_Control(pDX, IDC_EDIT6, Ballon);
	DDX_Control(pDX, IDC_EDIT7, Wizard);
	DDX_Control(pDX, IDC_EDIT8, Healer);
	DDX_Control(pDX, IDC_EDIT9, Dragon);
	DDX_Control(pDX, IDC_EDIT10, Peka);
	DDX_Control(pDX, IDC_EDIT11, BabyDragon);
	DDX_Control(pDX, IDC_EDIT12, Miner);
	DDX_Control(pDX, IDC_EDIT13, Minion);
	DDX_Control(pDX, IDC_EDIT14, HogRider);
	DDX_Control(pDX, IDC_EDIT15, Valkyrie);
	DDX_Control(pDX, IDC_EDIT16, Golem);
	DDX_Control(pDX, IDC_EDIT17, Witch);
	DDX_Control(pDX, IDC_EDIT18, LavaHound);
	DDX_Control(pDX, IDC_EDIT19, BowLer);
	DDX_Control(pDX, IDC_EDIT20, LightingSpell);
	DDX_Control(pDX, IDC_EDIT21, HealingSpell);
	DDX_Control(pDX, IDC_EDIT22, RageSpell);
	DDX_Control(pDX, IDC_EDIT23, JumpSpell);
	DDX_Control(pDX, IDC_EDIT24, FreezeSpell);
	DDX_Control(pDX, IDC_EDIT25, CloneSpell);
	DDX_Control(pDX, IDC_EDIT26, PoisonSpell);
	DDX_Control(pDX, IDC_EDIT27, EarthquakeSpell);
	DDX_Control(pDX, IDC_EDIT28, HasteSpell);
	DDX_Control(pDX, IDC_EDIT29, SkeletonSpell);
	DDX_Control(pDX, IDC_CHECK1, IsSpeedUp);
	DDX_Control(pDX, IDC_EDIT30, SpeedUpBegin);
	DDX_Control(pDX, IDC_EDIT31, SpeedUpEnd);
	DDX_Control(pDX, IDC_AllCount, AllCount);
	DDX_Control(pDX, IDC_EDIT33, ElectroDragon);
	DDX_Control(pDX, IDC_EDIT32, Yeti);
	DDX_Control(pDX, IDC_EDIT34, IceGolem);
	DDX_Control(pDX, IDC_EDIT35, Headhunter);
}


BEGIN_MESSAGE_MAP(TabTrain, CDialog)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT1, &TabTrain::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &TabTrain::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &TabTrain::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &TabTrain::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &TabTrain::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &TabTrain::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &TabTrain::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &TabTrain::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, &TabTrain::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, &TabTrain::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, &TabTrain::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, &TabTrain::OnEnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, &TabTrain::OnEnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, &TabTrain::OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, &TabTrain::OnEnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, &TabTrain::OnEnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT17, &TabTrain::OnEnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, &TabTrain::OnEnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT19, &TabTrain::OnEnChangeEdit19)
	ON_EN_CHANGE(IDC_EDIT33, &TabTrain::OnEnChangeEdit33)
	ON_EN_CHANGE(IDC_EDIT32, &TabTrain::OnEnChangeEdit32)
	ON_EN_CHANGE(IDC_EDIT34, &TabTrain::OnEnChangeEdit34)
	ON_EN_CHANGE(IDC_EDIT35, &TabTrain::OnEnChangeEdit35)
END_MESSAGE_MAP()


void TabTrain::TotalInput()
{
	CString winText;
	int TotalArmy = 0;
	Barbarin.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText);
	Archer.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText);
	Giant.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 5;
	Goblin.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText);
	WallBreaker.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 2;
	Ballon.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 5;
	Wizard.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 4;
	Healer.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 14;
	Dragon.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 20;
	Peka.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 25;
	BabyDragon.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 10;
	Miner.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 6;
	ElectroDragon.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 30;
	Yeti.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 18;
	Minion.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 2;
	HogRider.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 5;
	Valkyrie.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 8;
	Golem.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 30;
	Witch.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 12;
	LavaHound.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 30;
	BowLer.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 6;
	IceGolem.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 15;
	Headhunter.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText) * 6;

	winText.Format("%d", TotalArmy);
	AllCount.SetWindowTextA(winText);
}

void TabTrain::OnEnChangeEdit1()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit2()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit3()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit4()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit5()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit6()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit7()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit8()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit9()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit10()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit11()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit12()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit13()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit14()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit15()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit16()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit17()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit18()
{
	TotalInput();
}


void TabTrain::OnEnChangeEdit19()
{
	TotalInput();
}


void TabTrain::OnPaint()
{
	CPaintDC dc(this);
}


void TabTrain::OnEnChangeEdit33()
{
	TotalInput();//电龙
}


void TabTrain::OnEnChangeEdit32()
{
	TotalInput();//雪怪
}


void TabTrain::OnEnChangeEdit34()
{
	TotalInput();//冰石
}


void TabTrain::OnEnChangeEdit35()
{
	TotalInput();//猎手
}

