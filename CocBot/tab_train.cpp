// TabTrain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cocBot.h"
#include "tab_train.h"
#include "afxdialogex.h"


// TabTrain �Ի���

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
}


BEGIN_MESSAGE_MAP(TabTrain, CDialog)
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
	ON_WM_PAINT()
END_MESSAGE_MAP()


// TabTrain ��Ϣ�������



void TabTrain::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::TotalInput()
{
	CString winText;
	int TotalArmy = 0;
	Barbarin.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText);

	Archer.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText);
	Giant.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*5;
	Goblin.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText);
	WallBreaker.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*2;
	Ballon.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*5;
	Wizard.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*4;
	Healer.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*14;
	Dragon.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*20;
	Peka.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*25;
	BabyDragon.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*10;
	Miner.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*5;
	Minion.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*2;
	HogRider.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*5;
	Valkyrie.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*8;
	Golem.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*30;
	Witch.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*12;
	LavaHound.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*30;
	BowLer.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*6;
	winText.Format("%d", TotalArmy);
	AllCount.SetWindowTextA(winText);
}


void TabTrain::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit5()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit7()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit8()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit9()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit10()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit11()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit12()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit13()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit14()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit15()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit16()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit17()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit18()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnEnChangeEdit19()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TotalInput();
}


void TabTrain::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	//CRect rect;
	//GetClientRect(rect);
	//dc.FillSolidRect(rect, RGB(0Xc0, 0Xc0, 0Xc0));
	//dc.FillPath();
}
