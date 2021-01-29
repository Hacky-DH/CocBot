// tab_quickset.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cocBot.h"

#include "tab_quickset.h"

#include "afxdialogex.h"


// TabQuickSet �Ի���

IMPLEMENT_DYNAMIC(TabQuickSet, CDialogEx)

TabQuickSet::TabQuickSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(TabQuickSet::IDD, pParent)
	, app_player_type(FALSE)
{
	app_player_type = 1;
}

TabQuickSet::~TabQuickSet()
{
}

void TabQuickSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO2, GameVersion);
	DDX_Control(pDX, IDC_CHECK1, OffLine);
	DDX_Control(pDX, IDC_CHECK2, RequestArmy);
	DDX_Control(pDX, IDC_CHECK3, Attack);
	DDX_Control(pDX, IDC_CHECK4, DonateArmy);
	DDX_Control(pDX, IDC_CHECK5, UpgradeWall);
	DDX_Control(pDX, IDC_CHECK6, UpgradeHeros);
	DDX_Control(pDX, IDC_CHECK7, ControlTroophs);
	DDX_Control(pDX, IDC_CHECK8, LightingDarkElixir);
	DDX_Control(pDX, IDC_CHECK9, RemoveTree);
	DDX_Control(pDX, IDC_CHECK10, RearmAll);
	DDX_Control(pDX, IDC_EDIT3, LoadOutSet);
	DDX_Control(pDX, IDC_EDIT5, LoadInSet);
	DDX_Control(pDX, IDC_COMBO6, townLevel);
	DDX_Control(pDX, IDC_CHECK_BS, check_bs);
	DDX_Radio(pDX, IDC_CHECK_BS, app_player_type);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(TabQuickSet, CDialog)

	ON_CBN_SELCHANGE(IDC_COMBO1, &TabQuickSet::OnBsOrOtherChange)
	ON_BN_CLICKED(IDC_BUTTON10, &TabQuickSet::OnLoadInConfig)
	ON_BN_CLICKED(IDC_BUTTON11, &TabQuickSet::OnLoadOutConfig)
	ON_BN_CLICKED(IDC_BUTTON2, &TabQuickSet::OnSelectFile)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BT_QUICKSET, &TabQuickSet::OnBnClickedBtQuickset)
	ON_BN_CLICKED(IDC_CHECK_BS, &TabQuickSet::OnBnClickedCheckBs)
	ON_BN_CLICKED(IDC_CHECK_LD, &TabQuickSet::OnBnClickedCheckLd)
END_MESSAGE_MAP()


// TabQuickSet ��Ϣ�������


void TabQuickSet::OnBsOrOtherChange()
{
}


void TabQuickSet::OnLoadInConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(hParent, WM_LOAD_IN_CONFIG, 0, 0);
}


void TabQuickSet::OnLoadOutConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(hParent, WM_LOAD_OUT_CONFIG, 0, 0);
}


void TabQuickSet::OnSelectFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CbotFunction* bot = new CbotFunction;
	CString filename;
	filename= bot->SelectFile("�����ļ�(*.ini)|*.ini||");
	delete bot;
	LoadInSet.SetWindowTextA(filename);
}


void TabQuickSet::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}


BOOL TabQuickSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void TabQuickSet::OnBnClickedBtQuickset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(hParent, WM_PAGE_1_TEST_MESSAGE, 0, 0);

}


void TabQuickSet::OnBnClickedCheckBs()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	::SendMessage(hParent, WM_SELECT_APP_PLAYER, app_player_type, 0);
}


void TabQuickSet::OnBnClickedCheckLd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	::SendMessage(hParent, WM_SELECT_APP_PLAYER, app_player_type, 0);
}
