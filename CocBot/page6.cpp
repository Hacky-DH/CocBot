// page6.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "page6.h"
#include "afxdialogex.h"


// page6 对话框

IMPLEMENT_DYNAMIC(page6, CDialogEx)

page6::page6(CWnd* pParent /*=NULL*/)
	: CDialogEx(page6::IDD, pParent)
{

}

page6::~page6()
{
}

void page6::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, UpgradeWallMinGold);
	DDX_Control(pDX, IDC_EDIT2, UpgradeWallMinElixir);
	DDX_Control(pDX, IDC_COMBO1, UpgradeWallUseType);
	DDX_Control(pDX, IDC_COMBO2, UpgradeWallLevel);
	DDX_Control(pDX, IDC_EDIT3, UpgradeHeroMinDarkElixir);
	DDX_Control(pDX, IDC_COMBO3, UpgradeHeroType);
}


BEGIN_MESSAGE_MAP(page6, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// page6 消息处理程序


void page6::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	/*CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0Xc0, 0Xc0, 0Xc0));
	dc.FillPath();*/
}
