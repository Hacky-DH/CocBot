#include "stdafx.h"
#include "cocBot.h"
#include "tab_stats.h"
#include "afxdialogex.h"


// TabStats 对话框

IMPLEMENT_DYNAMIC(TabStats, CDialog)

TabStats::TabStats(CWnd* pParent /*=NULL*/)
	: CDialog(TabStats::IDD, pParent)
{

}

TabStats::~TabStats()
{
}

void TabStats::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl1);
	DDX_Control(pDX, IDC_RunTime, RunTime);
	DDX_Control(pDX, IDC_AttackCount, AttackCount);
	DDX_Control(pDX, IDC_SearchCount, SearchCount);
	DDX_Control(pDX, IDC_THREADCOUNT, m_ThreadCount);
}


BEGIN_MESSAGE_MAP(TabStats, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// TabStats 消息处理程序


void TabStats::OnPaint()
{
	CPaintDC dc(this);
}
