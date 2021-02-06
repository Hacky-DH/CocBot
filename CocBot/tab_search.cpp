#include "stdafx.h"
#include "cocBot.h"
#include "tab_search.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(TabSearch, CDialog)

TabSearch::TabSearch(CWnd* pParent /*=NULL*/)
	: CDialog(TabSearch::IDD, pParent)
{

}

TabSearch::~TabSearch()
{
}

void TabSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, MinTroopRet);
	DDX_Control(pDX, IDC_CHECK1, IsWaitBarbarinKing);
	DDX_Control(pDX, IDC_CHECK2, IsWaitArcherKing);
	DDX_Control(pDX, IDC_CHECK3, IsWaitGrandKing);
	DDX_Control(pDX, IDC_CHECK4, IsWaitClanCastleTroopsAndSpells);
	DDX_Control(pDX, IDC_EDIT8, MinTroophs);
	DDX_Control(pDX, IDC_EDIT9, MaxTroophs);
	DDX_Control(pDX, IDC_EDIT2, SearchMinGold);
	DDX_Control(pDX, IDC_EDIT3, SearchMinElixir);
	DDX_Control(pDX, IDC_EDIT4, SearchMinDarkElixir);
	DDX_Control(pDX, IDC_COMBO1, SearchType);
	DDX_Control(pDX, IDC_COMBO2, SearchDeadbaseGoldCollector);
	DDX_Control(pDX, IDC_COMBO3, SearchDeadbaseElixir);
	DDX_Control(pDX, IDC_CHECK6, ArcherTower);
	DDX_Control(pDX, IDC_COMBO4, ArcherTowerLevel);
	DDX_Control(pDX, IDC_CHECK7, Mortar);
	DDX_Control(pDX, IDC_COMBO5, MortarLevel);
	DDX_Control(pDX, IDC_CHECK8, WizardTower);
	DDX_Control(pDX, IDC_COMBO6, WizardTowerLevel);
	DDX_Control(pDX, IDC_CHECK9, AirDefense);
	DDX_Control(pDX, IDC_COMBO7, AirDefenseLevel);
	DDX_Control(pDX, IDC_CHECK10, XBow);
	DDX_Control(pDX, IDC_COMBO8, XBowLevel);
	DDX_Control(pDX, IDC_CHECK11, Inferno);
	DDX_Control(pDX, IDC_COMBO9, InfernoLevel);
	DDX_Control(pDX, IDC_CHECK12, EagleArtillery);
	DDX_Control(pDX, IDC_COMBO10, EagleArtilleryLevel);
	DDX_Control(pDX, IDC_EDIT5, SearchDelay);
	DDX_Control(pDX, IDC_EDIT6, SearchWait);
	DDX_Control(pDX, IDC_EDIT7, SearchMaxCount);
	DDX_Control(pDX, IDC_CHECK5, IsWaitSpell);
}


BEGIN_MESSAGE_MAP(TabSearch, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// TabSearch 消息处理程序


void TabSearch::OnPaint()
{
	CPaintDC dc(this);
}
