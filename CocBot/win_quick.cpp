// win_quick.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cocBot.h"

#include "win_quick.h"

#include "afxdialogex.h"


// win_quick �Ի���

IMPLEMENT_DYNAMIC(win_quick, CDialogEx)

win_quick::win_quick(CWnd* pParent /*=NULL*/)
	: CDialogEx(win_quick::IDD, pParent)
	, app_player_type(FALSE)
{
	app_player_type = 1;
}

win_quick::~win_quick()
{
}

void win_quick::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(win_quick, CDialog)

	ON_CBN_SELCHANGE(IDC_COMBO1, &win_quick::OnBsOrOtherChange)
	ON_BN_CLICKED(IDC_BUTTON10, &win_quick::OnLoadInConfig)
	ON_BN_CLICKED(IDC_BUTTON11, &win_quick::OnLoadOutConfig)
	ON_BN_CLICKED(IDC_BUTTON2, &win_quick::OnSelectFile)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BT_QUICKSET, &win_quick::OnBnClickedBtQuickset)
	ON_BN_CLICKED(IDC_CHECK_BS, &win_quick::OnBnClickedCheckBs)
	ON_BN_CLICKED(IDC_CHECK_LD, &win_quick::OnBnClickedCheckLd)
END_MESSAGE_MAP()


// win_quick ��Ϣ�������


void win_quick::OnBsOrOtherChange()
{
}


void win_quick::OnLoadInConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(hParent, WM_LOAD_IN_CONFIG, 0, 0);
}


void win_quick::OnLoadOutConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(hParent, WM_LOAD_OUT_CONFIG, 0, 0);
}


void win_quick::OnSelectFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CbotFunction* bot = new CbotFunction;
	CString filename;
	filename= bot->SelectFile("�����ļ�(*.ini)|*.ini||");
	delete bot;
	LoadInSet.SetWindowTextA(filename);
}


void win_quick::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}


BOOL win_quick::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void win_quick::OnBnClickedBtQuickset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(hParent, WM_PAGE_1_TEST_MESSAGE, 0, 0);

}


void win_quick::OnBnClickedCheckBs()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	::SendMessage(hParent, WM_SELECT_APP_PLAYER, app_player_type, 0);
}


void win_quick::OnBnClickedCheckLd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	::SendMessage(hParent, WM_SELECT_APP_PLAYER, app_player_type, 0);
}
