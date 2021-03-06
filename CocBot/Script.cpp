#include "stdafx.h"
#include "Script.h"
#include <mmsystem.h>
#include "lua_func.h"
#include "ImageLib.h"
#define AVOID_ZERO(x) ((x)==0?1:(x))

CScript::CScript()
{
	scriptVer = cocBotVer;
	scriptInfo = 0;
	attackArmy.archer = 0;
	attackArmy.babarin = 0;
	attackArmy.giant = 0;
	attackArmy.goblin = 0;
	attackArmy.wallbreaker = 0;
	attackArmy.wizard = 0;
	SwitchNo = 0;
	bindHwnd = 0;
	AppCocID = 0;
	AppPlayerType = 0;
	IsSwitch = false;
	IsThreadRunSuspend = false;
}


CScript::~CScript()
{

}


void CScript::Notify() {
	CString file = GetCurrentPath() + "\\notify.wav";
	if (PathFileExists(file))
		PlaySound(file, NULL, SND_FILENAME | SND_ASYNC);
}

long CScript::GetScriptState()
{
	return scriptInfo;
}


CString CScript::GetCurrentPath()
{
	TCHAR tcExePath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, tcExePath, MAX_PATH);
	TCHAR *pFind = _tcsrchr(tcExePath, '\\');
	if (pFind == NULL)
	{
		return 0;
	}
	*pFind = '\0';
	CString szIniPath = tcExePath;
	szIniPath = szIniPath + _T("\\");
	return szIniPath;
}


bool CScript::CreateDm(int type)
{

	::CoInitialize(NULL);
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);

	if (dm.CreateDispatch(clsid) == TRUE)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void CScript::Delay(unsigned long mSeconds)
{
	DWORD t1 = GetTickCount();
	for (; GetTickCount() - t1 < mSeconds;)
	{
		if (false == IsThreadRun) break;
		Sleep(1);
	}
}


void CScript::DelayRandTime(unsigned long minDeaySeconds, unsigned long maxDelaySeconds)
{
	if (!IsDelay)
		return;
	CString str;
	DWORD s = GetTickCount() / 2555;
	srand(s);
	if (minDeaySeconds >= maxDelaySeconds)
	{
		maxDelaySeconds = minDeaySeconds + 10;
	}
	long resultRand = minDeaySeconds + (rand() % (maxDelaySeconds - minDeaySeconds));
	str.Format("随机延迟:%ld s", resultRand);
	SetLog(str, true, BLUECOLOR, false);
	resultRand *= 1000;
	Delay(resultRand);
}


void CScript::LeftClick(long x, long y, unsigned long delay)
{
	dm.MoveTo(x, y);
	Delay(delay);
	dm.LeftClick();
}


int CScript::KillAdb()
{
	CString str;
	int ret = 0;
	str = dm.EnumProcess("adb.exe");
	if (str.GetLength() > 0)
	{
		coc.KillProcessById(_ttoi(str));
		ret += 1;
	}
	str = dm.EnumProcess("nox_adb.exe");
	if (str.GetLength() > 0)
	{
		coc.KillProcessById(_ttoi(str));
		ret += 1;
	}
	str = dm.EnumProcess("HD-Adb.exe");
	if (str.GetLength() > 0)
	{
		coc.KillProcessById(_ttoi(str));
		ret += 1;
	}
	return ret;
}


int CScript::SelectSolider(int type)
{
	// type是兵编号
	const int minY = 572;
	const int maxY = 597;
	int x, y;
	CString str;
	SetPath("\\Pic\\attack\\solider");
	str.Format("solider_%d.bmp|solider_%d_2.bmp", type, type);
	int loc_ret = ImageLoc(25, 570, 833, 650, str, 0.9, x, y);
	long x1 = 0, x2 = 0;
	CString armyNum;
	int solider_num = 0;
	if (loc_ret == 1)
	{
		dm.UseDict(DICT_COC_ATTACKARMY);
		MakeRect(x, &x1, &x2);
		armyNum = dm.Ocr(x1, minY, x2, maxY, "ffffff-0f0f0f", 0.85);
		str.Format("选择 %s\t%s", ARMYNAME[type - 1], armyNum);
		SetLog(str, true, BLACKCOLOR);
		if (armyNum.GetLength() > 0)
		{
			if (armyNum.Left(1) == "x")
			{
				armyNum = armyNum.Right(armyNum.GetLength() - 1);
			}
		}
		LeftClick(x, 610, 20);
		solider_num = _ttoi(armyNum);
		if (solider_num == 0) solider_num = 1;
	}
	else
	{
		solider_num = 0;
	}
	return solider_num;
}


int CScript::SelectSpell(int type)
{
	const int minY = 572;
	const int maxY = 597;
	int x, y;
	CString str;
	SetPath("Pic\\attack\\spell\\");
	str.Format("spell_%d.bmp", type);
	ImageLoc(25, 570, 833, 650, str, 0.95, x, y);
	long x1 = 0, x2 = 0;
	int solider_num = 0;
	CString armyNum;
	if (x > 0)
	{
		dm.UseDict(DICT_COC_ATTACKARMY);
		MakeRect(x, &x1, &x2);
		armyNum = dm.Ocr(x1, minY, x2, maxY, "ffffff-0f0f0f", 0.85);
		str.Format("%d\t%s", type, armyNum);
		SetLog(str);
		//SetLog(armyNum);
		if (armyNum.GetLength() > 0)
		{
			if (armyNum.Left(1) == "x")
			{
				armyNum = armyNum.Right(armyNum.GetLength() - 1);
			}
		}
		dm.MoveTo(x, 608);
		Delay(20);
		dm.LeftClick();
		solider_num = _ttoi(armyNum);
		if (solider_num == 0)solider_num = 1;
	}
	else
	{
		solider_num = 0;
	}
	return solider_num;
}


int CScript::SelectHero(int type)
{
	const int minY = 572;
	const int maxY = 597;
	int x, y;
	CString str;
	SetPath("\\Pic\\attack\\king\\");
	str.Format("king_%d.bmp", type);
	ImageLoc(25, 570, 833, 650, str, 0.95, x, y);
	if (x > 0)
	{
		LeftClick(x, y);
		return x;
	}
	return 0;
}

int CScript::ImageLoc(long x1, long y1, long x2, long y2, const char* file, double sim, int&ret_x, int&ret_y)
{
	ret_x = ret_y = -1;
	using namespace std;
	vector<string>vstr;
	string mfile;
	_split(file, vstr, "|");
	if (vstr.size() == 0)return -1;
	for (size_t i = 0; i < vstr.size(); i++)
	{
		mfile += m_file_path;
		mfile += file;
		mfile += "|";

	}
	mfile.pop_back();
	void* p = (void*)dm.GetScreenData(x1, y1, x2, y2);
	int retx, rety;
	int ret = ::ImageLoc(x2 - x1, y2 - y1, p, mfile.c_str(), sim, &retx, &rety);

	if (ret == 1)
	{
		retx += x1;
		rety += y1;
		ret_x = retx;
		ret_y = rety;
	}
	return ret;
}


int CScript::RepairPos(long x, long y, int type, long* resultX, long* resultY)
{
	switch (type)
	{
	case 0:
		*resultX = x - 10;
		*resultY = y - 10;
		break;
	case 1:
		*resultX = x - 10;
		*resultY = y + 10;
		break;
	case 2:
		*resultX = x + 10;
		*resultY = y + 10;
		break;
	case 3:
		*resultX = x + 10;
		*resultY = y - 10;
		break;
	}

	return 0;
}


int CScript::AttackArea(long x1, long y1, long x2, long y2, long type, long* result_x, long* result_y)
{
	*result_x = 0;
	*result_y = 0;
	dm.SetPath(_T("\\Pic\\attack\\normal"));
	CString PicName;
	CString result;
	PicName = dm.MatchPicName("d_*.bmp");
	VARIANT x, y;
	dm.FindPic(x1, y1, x2, y2, PicName, "0f0f0f", 0.95, type, &x, &y);
	result = dm.FindPicEx(x1, y1, x2, y2, PicName, "0f0f0f", 0.95, type);
	if (x.lVal > 0)
	{
		*result_x = x.lVal;
		*result_y = y.lVal;
		return 1;
	}
	else
	{
		*result_x = 425;
		*result_y = 333;
	}


	return 0;
}


int CScript::ClearAdvirtisment()
{

	dm.SetPath("\\Advirtisment");
	CString pic_name;
	VARIANT x, y;
	pic_name = dm.MatchPicName("*.bmp");
	if (pic_name.GetLength() > 4)
	{
		if (dm.FindPic(0, 0, APP_RESOLUTION_X, APP_RESOLUTION_Y, pic_name, "0f0f0f", 0.85, 0, &x, &y))
		{
			dm.MoveTo(x.lVal + 5, y.lVal + 5);
			Delay(20);
			dm.LeftClick();
			//SetLog("发现广告，尝试清除", true, RGB(0xff, 0x00, 0x00), false);
			return 1;
		}


	}
	return 0;
}


int CScript::WaitForMainScreen()
{
	//if (lua_call_script("test.lua") == 0)
	//	return 1;
	dm.SetPath(_T("\\Pic\\others\\checkMainScreen"));
	int waitTime = 0;
	VARIANT x, y;
	CString showStr;
	CString PicName, result;
	PicName = dm.MatchPicName("main_screen*.bmp");
	do
	{
		if (_ttoi(coc.getSets("DebugLocateAD")) == 1)
		{
			ClearAdvirtisment();
		}
		dm.SetPath(_T("\\Pic\\others\\checkMainScreen"));
		dm.FindMultiColor(12, 5, 837, 51, "3abded-0f0f0f",
			"30|-1|37bfed-0f0f0f,786|7|fff655-0f0f0f,796|9|ffec22-0f0f0f",
			1.0, 0, &x, &y);
		//成功
		if (x.lVal > 0)
		{
			return 1;
		}
		showStr.Format("加载村庄中,最长等待：%ds", 300 - waitTime);
		if (waitTime % 10 == 0)
		{
			checkScreenError();
			SetLog(showStr, true, BLACKCOLOR, false);
		}
		else
		{
			SetLog(showStr, false, BLACKCOLOR, false);
		}
		if (waitTime >= 300)
		{
			scriptInfo = ShouldRestart;
			SetLog(_T("未发现村庄，尝试重启"), true, REDCOLOR, true);
			return -1;
		}
		waitTime++;
		Delay(1000);
	} while (IsThreadRun);
	return -1;
}


int CScript::RequestHelp()
{
	VARIANT x, y;
	dm.SetPath("\\Pic\\others\\RequestHelp");
	dm.FindPic(638, 495, 796, 572, "RequestHelp.bmp", "0f0f0f", 0.9, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Delay(20);
		dm.LeftClick();
		Delay(1500);
		dm.FindMultiColor(357, 133, 509, 173, "ffffff-0f0f0f", "63|6|ffffff-0f0f0f", 1.0, 1, &x, &y);
		if (x.lVal > 0)
		{
			LeftClick(x.lVal, y.lVal);
			Delay(1000);
			if (_ttoi(coc.getSets("IsChangeWords")) == 1)
			{
				dm.SendString(bindHwnd, coc.getSets("requestWords"));
			}
			Delay(1000);
		}
		dm.FindMultiColor(442, 194, 596, 262, "c9e870-0f0f0f", "68|0|c8e870-0f0f0f,2|30|5dac10-0f0f0f,73|30|5cac10-0f0f0f", 1.0, 1, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Delay(20); dm.LeftClick();
		}
		else
		{
			dm.MoveTo(811, 92);
			Delay(20);
			dm.LeftClick();
		}
	}
	return 0;
}


int CScript::CheckArmyNum(int* trainT)
{
	SetLog("查看军队情况", true, BLUECOLOR, false);
	SetPath("\\Pic\\others");
	int retx, rety;
	while (true) {
		Delay(500);
		ImageLoc(19, 501, 60, 542, "army_view.bmp", 0.95, retx, rety);
		if (retx > 0 && rety > 0)
			LeftClick(retx, rety);
		else
			LeftClick(39, 517);
		if (1 == WaitPic(797, 75, 835, 110, "close_view.bmp", 3000, false))
			break;
	}
	CString armyStr, siege_str, M_time, time_str, spells_str, clancastle_str, clan_spell, clan_siege, ret_str;
	int NowCount = 0, AllCount = 1;
	dm.UseDict(0);
	Delay(200);
	armyStr = dm.Ocr(75, 134, 155, 157, "ffffff-050505", 0.85);
	if (armyStr.IsEmpty())
		armyStr.Format("0/%d", army_capacity);
	vector<CString> vstr;
	Split(armyStr, vstr, "/");
	AllCount = vstr.size() == 2 ?  _ttoi(vstr[1]) : army_capacity;
	NowCount = _ttoi(vstr[0]);
	float ret = AllCount > 0 ? (((float)NowCount * 100) / (float)AllCount) : 0.0f;
	LootRecord[SwitchNo].ArmyRet = ret;
	LootRecord[SwitchNo].CurrentArmyNum = NowCount;
	int pos = ret > 100 ? 0 : (int)ret;
	if (pProgress) pProgress->SetPos(pos);
	M_time = dm.Ocr(470, 126, 580, 156, "ffffff-050505", 0.85);
	siege_str = dm.Ocr(674, 133, 709, 153, "ffffff-050505", 0.85);
	spells_str = dm.Ocr(75, 283, 125, 302, "ffffff-050505", 0.85);
	clancastle_str = dm.Ocr(125, 435, 175, 456, "ffffff-050505", 0.85);
	clan_spell = dm.Ocr(467, 431, 506, 450, "ffffff-050505", 0.85);
	clan_siege = dm.Ocr(640, 429, 675, 449, "ffffff-050505", 0.85);
	ImageLoc(470, 126, 580, 156, "minutes_1.bmp", 0.8, retx, rety);
	if (M_time.IsEmpty())
	{
		 M_time = time_str = "0";
	}
	M_time += retx > 0 ?  _T("分钟") : _T("秒");
	if (M_time.Find(_T("分钟")) != -1)
	{
		time_str = M_time.Left(M_time.Find(_T("分钟")));
	}
	else
	{
		if (time_str != "0"&&M_time.Find("秒") != -1)
		{
			time_str = "1";
		}
	}
	*trainT = _ttoi(time_str);
	ret_str.Format("[部队] %s(%0.2f%%) [造兵时间]%s [攻城机器] %s",
		armyStr, ret, M_time, siege_str);
	SetLog(ret_str, true, BLACKCOLOR, false);
	ret_str.Format("[法术] %s [部落援军] %s [部落法术] %s [部落攻城机器] %s", 
		spells_str, clancastle_str, clan_spell, clan_siege);
	SetLog(ret_str, true, BLACKCOLOR, false);
	if (_ttoi(coc.getSets("RequestArmy")) == 1)
	{
		RequestHelp();
		Delay(100);
	}
	SetPath("\\Pic\\others\\");
	if (1 != WaitPic(797, 75, 835, 110, "close_view.bmp", 3000, true))
	{
		SetLog("找不到 close_view.bmp.", true, REDCOLOR);
		return -1;
	}
	ImageLoc(797, 75, 835, 110, "close_view.bmp", 0.95, retx, rety);
	if (retx > 0)
	{
		LeftClick(retx, rety);
	}
	return ret >= _ttoi(coc.getSets("MinTroopRet")) ? 1 : 0;
}


void CScript::ClearArmy()
{
	SetLog("准备强制清兵");
	dm.UseDict(0);
	CString str;
	std::vector<CString> vstr;
	int cur = 1, total, retx, rety;
	SetPath("\\Pic\\others");
	do
	{
		// 识别备用的兵的数量
		Delay(1000);
		str = dm.Ocr(44, 126, 114, 144, "ffffff-050505", 0.85);
		Split(str, vstr, "/");
		if (vstr.size() < 2) return;
		cur = _ttoi(vstr[0]);
		total = _ttoi(vstr[1]);
		// 当前的兵数量减去总兵数的一半是要清理的数
		cur = cur - total / 2;
		if (cur > 0) {
			for (int i = 0; i < cur; i++)
			{
				ImageLoc(797, 156, 830, 185, "clear_army.bmp", 0.95, retx, rety);
				if (retx > 0 && rety > 0)
					LeftClick(retx, rety);
				else
					break;
				//LeftClick(810, 170);
				Delay(100);
			}
		}
	} while (cur > 0);
	SetLog("完成强制清兵");
}


int CScript::SpeedTrain()
{
	CString str_begin, str_end;
	str_begin = coc.getSets("SpeedUpBegin");
	str_end = coc.getSets("SpeedUpEnd");
	int nowh = _ttoi(coc.GetNowTime(3).Left(2));
	if (nowh >= _ttoi(str_begin) && nowh <= _ttoi(str_end))
	{
		VARIANT x, y;
		dm.SetPath("\\Pic\\others");
		dm.FindPic(695, 262, 831, 328, "speed_1.bmp", "0f0f0f", 0.85, 0, &x, &y);
		if (x.lVal > 0)
		{
			LeftClick(x.lVal, y.lVal);
			Delay(2500);
		}
		dm.FindPic(347, 372, 514, 454, "speed_2.bmp", "0f0f0f", 0.85, 0, &x, &y);
		if (x.lVal > 0)
		{
			LeftClick(x.lVal, y.lVal);
			Delay(2500);
			return 1;
		}
	}
	return 0;
}


int CScript::MakeArmy()
{
	int retx, rety;
	//士兵数量
	int purple_army_num[] = {
		_ttoi(coc.getSets("Barbarin")),
		_ttoi(coc.getSets("Archer")),
		_ttoi(coc.getSets("Giant")),
		_ttoi(coc.getSets("Goblin")),
		_ttoi(coc.getSets("WallBreaker")),
		_ttoi(coc.getSets("Ballon")),
		_ttoi(coc.getSets("Wizard")),
		_ttoi(coc.getSets("Healer")),
		_ttoi(coc.getSets("Dragon")),
		_ttoi(coc.getSets("Peka")),
		_ttoi(coc.getSets("BabyDragon")),
		_ttoi(coc.getSets("Miner")),
		_ttoi(coc.getSets("ElectroDragon")),
		_ttoi(coc.getSets("Yeti")),
	};
	int dark_army_num[] = {
		_ttoi(coc.getSets("Minion")),
		_ttoi(coc.getSets("HogRider")),
		_ttoi(coc.getSets("Valkyrie")),
		_ttoi(coc.getSets("Golem")),
		_ttoi(coc.getSets("Witch")),
		_ttoi(coc.getSets("LavaHound")),
		_ttoi(coc.getSets("BowLer")),
		_ttoi(coc.getSets("IceGolem")),
		_ttoi(coc.getSets("Headhunter")),
	};
	int spell_num[] = { 
		_ttoi(coc.getSets("LightingSpell")),
		_ttoi(coc.getSets("HealingSpell")),
		_ttoi(coc.getSets("RageSpell")),
		_ttoi(coc.getSets("JumpSpell")),
		_ttoi(coc.getSets("FreezeSpell")),
		_ttoi(coc.getSets("CloneSpell")),
		_ttoi(coc.getSets("InvisibilitySpell")),
		_ttoi(coc.getSets("PoisonSpell")),
		_ttoi(coc.getSets("EarthquakeSpell")),
		_ttoi(coc.getSets("HasteSpell")),
		_ttoi(coc.getSets("SkeletonSpell")),
		_ttoi(coc.getSets("BatSpell")),
	};
	//**************造兵***************//
	attackArmy.babarin = purple_army_num[0];
	attackArmy.archer = purple_army_num[1];
	attackArmy.giant = purple_army_num[2];
	attackArmy.goblin = purple_army_num[3];
	attackArmy.wallbreaker = purple_army_num[4];
	attackArmy.wizard = purple_army_num[5];
	// 打开军队
	SetPath("\\Pic\\others");
	while (true) {
		Delay(500);
		ImageLoc(19, 501, 60, 542, "army_view.bmp", 0.95, retx, rety);
		if (retx > 0 && rety > 0)
			LeftClick(retx, rety);
		else
			LeftClick(39, 517);
		if (1 == WaitPic(797, 75, 835, 110, "close_view.bmp", 3000, false))
			break;
	}
	//打开训练页
	Delay(1000);
	ImageLoc(259, 82, 342, 109, "army_view_2.bmp", 0.95, retx, rety);
	if (retx > 0)
		LeftClick(retx, rety);
	else
		LeftClick(238, 100);
	Delay(1000);
	dm.UseDict(0);
	CString str;
	std::vector<CString> vstr;
	str = dm.Ocr(44, 126, 114, 144, "ffffff-050505", 0.85);
	Split(str, vstr, "/");
	int NowCount = 0, AllCount = army_capacity * 2;
	if (vstr.size() > 1) {
		NowCount = _ttoi(vstr[0]);
		AllCount = _ttoi(vstr[1]);
	}
	if (AllCount <= 0) 
	{
		AllCount = army_capacity * 2;
	}
	if (NowCount * 100 / AllCount >= _ttoi(coc.getSets("MinTroopRet")))
	{
		LeftClick(814, 95); // 关闭军队
		return 1;
	}
	int IsClear = _ttoi(coc.getSets("IsClearArmy"));
	if (IsClear == 1)
		ClearArmy();
	int TrainArmyStyle = 0;
	TrainArmyStyle = _ttoi(coc.getSets("TrainArmyStyle"));
	CString pic_name;
	if (TrainArmyStyle == 0)
	{
		SetLog("自定义造兵");
		SetPath("\\Pic\\others\\solider\\");
		for (int i = 1; i <= 14; i++)
		{
			if (purple_army_num[i - 1] == 0)//无需造此兵
			{
				continue;
			}
			pic_name.Format("purple_solider_%d.bmp", i);
			ImageLoc(21, 335, 839, 548, pic_name, 0.95, retx, rety);
			if (retx > 0)
			{
				for (int j = 1; j <= purple_army_num[i - 1]; j++)
				{
					LeftClick(retx, rety);
					Delay(150);
				}
			}
			else
			{
				SetLog("找不到  " + pic_name, true, REDCOLOR, false);
			}
			Delay(500);
		}
		adbSwipe(800, 440, 200, 440); //向右拖拉
		Delay(1000);
		for (int i = 1; i <= 9; i++)//黑水兵
		{
			if (dark_army_num[i - 1] == 0)
			{
				continue;
			}
			pic_name.Format("dark_solider_%d.bmp", i);
			ImageLoc(21, 335, 839, 548, pic_name, 0.95, retx, rety);
			if (retx > 0)
			{
				for (int j = 1; j <= dark_army_num[i - 1]; j++)
				{
					LeftClick(retx, rety);
					Delay(150);
				}
			}
			else
			{
				SetLog("找不到  " + pic_name, true, REDCOLOR, false);
			}
			Delay(500);
		}
	}
	if (_ttoi(coc.getSets("IsSpeedUp")) == 1)
	{
		SpeedTrain();
	}
	if (TrainArmyStyle >= 1)
	{
		str.Format("一键训练，使用配置%d", TrainArmyStyle);
		SetLog(str);
		SetPath("\\Pic\\others\\");
		ImageLoc(636, 77, 781, 117, "army_view_5.bmp", 0.95, retx, rety);
		if (retx > 0)
			LeftClick(retx, rety);
		else
			LeftClick(710, 100);
		Delay(1000);
		switch (TrainArmyStyle)
		{
		case 1:
			ImageLoc(690, 239, 823, 340, "onekey_train.bmp", 0.80, retx, rety);
			if (retx < 0)
			{
				retx = 750;
				rety = 310;
			}
			LeftClick(retx, rety);
			break;
		case 2:
			ImageLoc(708, 346, 823, 439, "onekey_train.bmp", 0.80, retx, rety);
			if (retx < 0)
			{
				retx = 750;
				rety = 420;
			}
			LeftClick(retx, rety);
			break;
		case 3:
			ImageLoc(708, 454, 823, 550, "onekey_train.bmp", 0.80, retx, rety);
			if (retx < 0)
			{
				retx = 750;
				rety = 520;
			}
			LeftClick(retx, rety);
			break;
		case 4:
			adbSwipe(400, 580, 400, 100); //向上拖拉
			Delay(1500);
			ImageLoc(708, 300, 823, 370, "onekey_train.bmp", 0.80, retx, rety);
			if (retx < 0)
			{
				retx = 750;
				rety = 340;
			}
			LeftClick(retx, rety);
			break;
		case 5:
			adbSwipe(400, 580, 400, 100); //向上拖拉
			Delay(1500);
			ImageLoc(708, 420, 823, 470, "onekey_train.bmp", 0.80, retx, rety);
			if (retx < 0)
			{
				retx = 750;
				rety = 450;
			}
			LeftClick(retx, rety);
			break;
		case 6:
			adbSwipe(400, 580, 400, 100); //向上拖拉
			Delay(1500);
			ImageLoc(708, 530, 823, 580, "onekey_train.bmp", 0.80, retx, rety);
			if (retx < 0)
			{
				retx = 750;
				rety = 550;
			}
			LeftClick(retx, rety);
			break;
		}
	}
	//打开 spell
	SetPath("Pic\\others\\");
	ImageLoc(445, 83, 559, 114, "army_view_3.bmp", 0.95, retx, rety);
	if (retx > 0)
		LeftClick(retx, rety);
	else
		LeftClick(387, 100);//548
	Delay(1000);
	SetPath("\\Pic\\others\\solider");
	for (int i = 1; i <= 12; i++)
	{
		if (spell_num[i - 1] <= 0)
		{
			continue;
		}
		pic_name.Format("spell_%d.bmp", i);
		ImageLoc(21, 335, 839, 548, pic_name, 0.95, retx, rety);
		if (retx > 0)
		{
			for (int j = 1; j <= spell_num[i - 1]; j++)
			{
				LeftClick(retx, rety);
				Delay(150);
			}
		}
		else
		{
			//SetLog("找不到  " + pic_name, true, REDCOLOR, false);
		}
		Delay(500);
	}
	LeftClick(814, 95); // 关闭军队
	return 0;
}


int CScript::adbCmd(CString strCmd)
{
	CString strOut;
	const int max_size = 512;
	char buffer[max_size] = { 0 };
	//这里确定模拟器种类，并获得对应参数
	if (AppPlayerType == APP_PLAYER_LIGHTING)
	{
		//雷电专用
		adbCmd(AppPlayerIndex, strCmd);
		return 0;
	}
	//先adb device
	adb.start(appPlayerInstallDir + "\\HD-Adb.exe devices");
	adb.stop();
	SetLog(adb.get_result());
	//2.选择对应的端口进行连接

	adb.start(appPlayerInstallDir + "\\HD-Adb.exe shell");
	adb.RunCmd(strCmd);
	adb.stop();
	CString adb_error = adb.get_result();
	SetLog(adb_error, false, REDCOLOR, true);
	if (adb_error.Find("error: device not found") >= 0)
	{
		SetLog(_T("error: device not found,try to kill adb.exe!"), true, RGB(0xff, 0x00, 0x00), true);
		if (KillAdb())
		{
			SetLog(_T("kill adb.exe is ok, try to restart adb server"), true, RGB(0xff, 0x00, 0x00), true);
		}
		else
		{
			SetLog(_T("error:kill adb.exe 失败 请检查Adb 路径！ "), true, RGB(0xff, 0x00, 0x00), true);
		}
		adb.start(appPlayerInstallDir + "\\HD_Adb.exe shell");
		adb.RunCmd(strCmd);
		adb.stop();
		SetLog(adb.get_result(), false, REDCOLOR, true);

	}
	else if (adb_error.Find("device offline") >= 0)
	{
		SetLog(_T("error: device offline,try to kill adb.exe!"), true, RGB(0xff, 0x00, 0x00), true);
		if (KillAdb())
		{
			SetLog(_T("kill adb.exe is ok, try to restart adb server"), true, RGB(0xff, 0x00, 0x00), true);
		}
		else
		{
			SetLog(_T("error:kill adb.exe 失败 请检查Adb 路径！ "), true, RGB(0xff, 0x00, 0x00), true);
		}
		adb.start(appPlayerInstallDir + "\\HD_Adb.exe shell");
		adb.RunCmd(strCmd);
		adb.stop();
		SetLog(adb.get_result(), false, REDCOLOR, true);

	}

	return 0;
}


int CScript::adbCmd(int index, CString cmd)
{
	CString str, out;
	str.Format(" adb --index %d --command ", index);
	str += "\"shell ";
	str += cmd;
	str += "\"";
	adb.start(appPlayerInstallDir + "\\dnconsole.exe" + str);
	adb.stop();
	out = adb.get_result();
	if (out.Find("error: device not found") >= 0)
	{
		SetLog(_T("error: device not found,try to kill adb.exe!"), true, REDCOLOR, true);
		if (KillAdb())
		{
			SetLog(_T("kill adb.exe is ok, try to restart adb server"), true, REDCOLOR, true);
		}
		else
		{
			SetLog(_T("error:kill adb.exe 失败 请检查Adb 路径！ "), true, REDCOLOR, true);
		}
		adb.start(appPlayerInstallDir + "\\dnconsole.exe" + str);
		adb.stop();
		out = adb.get_result();
		SetLog(out);
	}
	return 0;
}



int CScript::AddArmy()
{
	return 0;
}


int CScript::GetResource()
{
	CString gold, water, oil, troophs;
	dm.UseDict(2);
	Delay(20);
	gold = dm.Ocr(652, 19, 811, 45, "ffffff-030303", 0.8);
	water = dm.Ocr(655, 69, 806, 91, "ffffff-030303", 0.8);
	oil = dm.Ocr(702, 120, 800, 140, "ffffff-030303", 0.8);
	troophs = dm.Ocr(61, 78, 125, 104, "ffffff-030303", 0.8);
	if (LootRecord[SwitchNo].IsFirstRecord)
	{
		LootRecord[SwitchNo].SetStartResource(_ttoi(gold), _ttoi(water),
			_ttoi(oil), _ttoi(troophs));
	}
	LootRecord[SwitchNo].SetNowResource(_ttoi(gold), _ttoi(water),
		_ttoi(oil), _ttoi(troophs));
	return 0;
}


int CScript::send_LightngSpell()
{
	VARIANT x, y;
	dm.FindMultiColor(36, 593, 821, 638, "082cda-0f0f0f", "5|-1|104be2-0f0f0f,-2|2|0720de-0f0f0f,4|2|0e45de-0f0f0f", 0.9, 1, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal - 30);
		Delay(100);
		dm.LeftClick();
		return 1;
	}
	else
	{
		return 0;
	}
}


int CScript::LightingAttack(long darkelixir)
{
	long AttackLingtingMinDarkElixir = _ttoi(coc.getSets("AttackLingtingMinDarkElixir"));
	int UseLightingCount = _ttoi(coc.getSets("UseLightingCount"));
	long dx, dy;
	if (darkelixir < AttackLingtingMinDarkElixir)
	{
		return 0;
	}
	VARIANT dx1, dy1;
	Delay(200);
	dm.SetPath("\\Pic\\attack\\DarkElixir");
	CString dark_pic;
	dark_pic = dm.MatchPicName("*.bmp");
	if (dark_pic.GetLength() >= 3)
	{
		CString ResultPos = dm.FindPicEx(30, 30, 840, 650, dark_pic, "0f0f0f", 0.8, 0);
		//SetLog(ResultPos);
		for (int j = 0; j <= ResultPos.GetLength(); j += 7)
		{
			dm.FindPic(30, 30, 840, 650, dark_pic, "0f0f0f", 0.8, 0, &dx1, &dy1);
			if (dx1.lVal)
			{


				dx = dx1.lVal + 15, dy = dy1.lVal + 30;
				if (8 <= dx&&dx <= 132 && 132 <= dy&&dy <= 554)
				{
					dx = 0;
					dy = 0;
				}
				dm.MoveTo(dx, dy);

				for (int k = 0; k <= UseLightingCount; k++)
				{
					Delay(20);
					dm.LeftClick();
				}
				Delay(3000);
			}
		}

	}

	return 1;
}


int CScript::WaitForReturnHome()
{
	int AttackMinWaitTime = _ttoi(coc.getSets("AttackMinWaitTime"));
	VARIANT x, y;
	SetLog("下兵完成，等待战斗结束", true, RGB(0x00, 0x00, 0xff), false);
	//识别的资源（当前）
	long ntGold = 0, ntElixir = 0, ntDark = 0;
	//之前的资源（1s前）
	long nbGold = 0, nbElixir = 0, nbDark = 0;
	//最少资源
	long minGold, minElixir, minDark;
	minGold = _ttoi(coc.getSets("AttackExitGold"));
	minElixir = _ttoi(coc.getSets("AttackExitElixir"));
	minDark = _ttoi(coc.getSets("AttackExitDarkElixir"));
	//是否资源较少时推出
	int isExit = _ttoi(coc.getSets("AttackIsExitWhenLittleResource"));
	//资源无变化时间（s)
	int  nTime = 0;
	//识别的资源
	CString strGold, strElixir, strDark;
	//设置字库
	dm.UseDict(DICT_COC_FISH);
	CString str_t;
	do
	{
		dm.SetPath(_T("\\Pic\\attack"));
		if (false == IsThreadRun) return -1;
		dm.FindPic(392, 520, 462, 562, "return.bmp", "141414", 0.9, 0, &x, &y);
		Delay(100);

		strGold = dm.Ocr(46, 65, 121, 84, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.85);
		strElixir = dm.Ocr(44, 96, 121, 114, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.85);
		strDark = dm.Ocr(46, 121, 108, 143, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.85);
		ntGold = _ttoi(strGold), ntElixir = _ttoi(strElixir), ntDark = _ttoi(strDark);

		if (ntGold == nbGold&&ntElixir == nbElixir&&ntDark == nbDark)
		{
			nTime++;
			if (nTime % 5 == 0)
			{
				str_t.Format("%d", AttackMinWaitTime - nTime);
				SetLog("战斗将在" + str_t + "秒后结束", true, BLACKCOLOR, false);
			}
		}
		else
		{
			nTime = 0;
		}
		nbGold = ntGold, nbElixir = ntElixir, nbDark = ntDark;
		if (isExit == 1)
		{
			if ((ntGold <= minGold) && (ntElixir <= minElixir) && (ntDark <= minDark))
			{
				break;
			}
		}
		if (false == IsThreadRun) return -1;
		if (x.lVal > 0 || nTime > AttackMinWaitTime)
		{
			if (send_LightngSpell() == 1)
			{
				if (LightingAttack(ntDark))
				{
					Delay(2000);
				}
			}

			break;
		}
		Delay(1000);
	} while (nTime <= 255);
	SetLog("返回村庄", true, RGB(0xff, 0x00, 0xff), true);
	dm.MoveTo(x.lVal, y.lVal);
	Delay(20);
	dm.LeftClick();
	dm.MoveTo(66, 530);
	Delay(20);
	dm.LeftClick();
	Delay(2000);
	dm.MoveTo(500, 396);
	Delay(20);
	dm.LeftClick();
	Delay(200);
	dm.MoveTo(427, 540);
	Delay(2000);
	dm.LeftClick();
	return 0;
}


int CScript::Attack_Intel()
{
	Delay(1000);
	if (false == IsThreadRun) return -1;
	long AttackSpeed = 10, AttackChangeDelay = 10;
	AttackSpeed = _ttoi(coc.getSets("AttackSpeed")) / 2;
	AttackSpeed = (AttackSpeed + 1) * 10;
	AttackChangeDelay = _ttoi(coc.getSets("AttackGird"));
	AttackChangeDelay = (AttackChangeDelay + 1) * 10;
	SetPath("\\Pic\\attack");
	SetLog(_T("定位下兵位置"));
	//寻找所有下兵色块
	CString res, str;
	res = dm.FindColorBlockEx(35, 27, 794, 567, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f",
		0.99, 70, 10, 10);
	if (res.GetLength() <= 0) return -1;
	//所有坐标
	int nPos = dm.GetResultCount(res);
	long* allx = new long[nPos];
	long* ally = new long[nPos];
	/*初始化*/
	VARIANT tempx, tempy;
	/*获取所有坐标*/
	for (int i = 0; i < nPos; i++)
	{
		dm.GetResultPos(res, i, &tempx, &tempy);
		allx[i] = tempx.lVal;
		ally[i] = tempy.lVal;
	}

	//下兵坐标
	long x[MAX_ARMY_COUNT], y[MAX_ARMY_COUNT];
	/*寻求最优坐标*/
	int bestIndex = 0;

	for (int i = 0; i < MAX_ARMY_COUNT; i++)
	{
		bestIndex = Array::FindNearestPos<long>(allx, ally, nPos,
			ATTACK_CIRCLE_X[i], ATTACK_CIRCLE_Y[i]);
		x[i] = allx[bestIndex];
		y[i] = ally[bestIndex];
	}

	/*到这里，之前的大量坐标已经不需要了，删除*/
	delete[]allx, delete[]ally;
	SetLog(_T("定位完成"));
	//识别兵种数量
	int solider_num, total_num = 0, retry = 3, total_retry = 0;
	GetArmyMsg();
	//下兵间距
	float distance = 1;
	int currentArmyNum = LootRecord[SwitchNo].CurrentArmyNum;
	while (retry > 0) {
		/*巨人*/
		solider_num = SelectSolider(GIANT);
		total_num += solider_num * 5;
		if (solider_num > 0)
		{
			distance = MAX_ARMY_COUNT / solider_num;
			if (distance <= 0.0001)distance = 1;
			for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
			{
				LeftClick(x[i], y[i]);
			}
		}
		Delay(AttackChangeDelay);
		/*野蛮人*/
		solider_num = SelectSolider(BARBARIN);
		total_num += solider_num;
		if (solider_num > 0)
		{
			distance = MAX_ARMY_COUNT / solider_num;
			if (distance <= 0.0001)distance = 1;
			for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
			{
				LeftClick(x[i], y[i]);
				Delay(AttackSpeed);
			}
		}
		Delay(AttackChangeDelay);
		/*炸弹人*/
		solider_num = SelectSolider(WALLBREAKER);
		total_num += solider_num * 2;
		if (solider_num > 0)
		{
			distance = MAX_ARMY_COUNT / solider_num;
			if (distance <= 0.0001)distance = 1;
			for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
			{
				LeftClick(x[i], y[i]);
				Delay(AttackSpeed);
			}
		}
		Delay(AttackChangeDelay);
		/*弓箭手*/
		solider_num = SelectSolider(ARCHER);
		total_num += solider_num;
		if (solider_num > 0)
		{
			distance = MAX_ARMY_COUNT / solider_num;
			if (distance <= 0.0001)distance = 1;
			for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
			{
				LeftClick(x[i], y[i]);
				Delay(AttackSpeed);
			}
		}
		Delay(AttackChangeDelay);
		/*哥布林*/
		solider_num = SelectSolider(GOBLIN);
		total_num += solider_num;
		if (solider_num > 0)
		{
			distance = MAX_ARMY_COUNT / solider_num;
			if (distance <= 0.0001)distance = 1;
			for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
			{
				LeftClick(x[i], y[i]);
				Delay(AttackSpeed);
			}
		}
		if (total_num < currentArmyNum) {
			str.Format("实际下兵数量%d小于总兵数%d", total_num, currentArmyNum);
			SetLog(str, true, REDCOLOR, true);
			if (total_num <= 0) total_num = 1;
			retry = currentArmyNum % total_num;
		}
		retry--;
		total_retry++;
		Delay(1000);
		if (total_retry > 10) {
			break;
		}
	}
	/*释放援军
	VARIANT vx, vy;
	dm.FindMultiColor(25, 570, 827, 652, "84bce0-0f0f0f", "-26|22|5f97ce-0f0f0f,27|24|6297cc-0f0f0f,-11|45|4b6e8f-0f0f0f,17|42|4a6f95-0f0f0f", 0.9, 1, &vx, &vy);//释放 援军
	if (vx.lVal > 0)
	{
		SetLog("释放援军", true, BLUECOLOR, false); dm.MoveTo(vx.lVal, vy.lVal); Delay(20); dm.LeftClick(); Delay(200); dm.MoveTo(x[0], y[0]); Delay(20); dm.LeftClick();
	}
	*/
	// 释放王
	int king1x = SelectHero(1);
	if (king1x > 0)
	{
		SetLog("释放蛮王", true, BLACKCOLOR);
		Delay(200);
		LeftClick(x[0], y[0]);
	}
	int king2x = SelectHero(2);
	if (king2x > 0)
	{
		SetLog("释放女王", true, BLACKCOLOR);
		Delay(200);
		LeftClick(x[120], y[120]);
	}
	int king3x = SelectHero(3);
	if (king3x > 0)
	{
		SetLog("释放守护者", true, BLACKCOLOR);
		Delay(200);
		LeftClick(x[180], y[180]);
	}
	Delay(2000);
	LeftClick(king1x, 618);
	Delay(1000);
	LeftClick(king2x, 618);
	Delay(1000);
	LeftClick(king3x, 618);
	Delay(2000);
	return 0;
}


int CScript::Attack_Equal()
{
	Delay(2000);
	if (false == IsThreadRun) return -1;
	CString xyStr, usestr;
	long AttackSpeed = 10, AttackChangeDelay = 10;
	AttackSpeed = _ttoi(coc.getSets("AttackSpeed"));
	AttackSpeed = (AttackSpeed + 1) * 10;
	AttackChangeDelay = _ttoi(coc.getSets("AttackGird"));
	AttackChangeDelay = (AttackChangeDelay + 1) * 10;
	dm.SetPath(_T("\\Pic\\attack"));
	SetLog(_T("定位下兵位置"), true, BLUECOLOR, false);
	//VARIANT x1, y1;
	int solider_num = 0; //
	float distance = 1.0;
	int attackcount = 0;
	CString attack_xy;
	CString result_posx[4] = {};
	//寻找所有下兵色块
	result_posx[0] = dm.FindColorBlockEx(44, 55, 445, 379, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	result_posx[1] = dm.FindColorBlockEx(32, 349, 447, 630, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	result_posx[2] = dm.FindColorBlockEx(426, 305, 768, 506, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	result_posx[3] = dm.FindColorBlockEx(428, 113, 707, 298, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	//下兵位置
	long x[4][61] = { 0 }, y[4][61] = { 0 };
	x[0][0] = 465, y[0][0] = 149;
	x[1][0] = 159, y[1][0] = 337;
	x[2][0] = 443, y[2][0] = 530;
	x[3][0] = 604, y[3][0] = 311;
	for (int i = 0; i < MAXATTACKCOUNT; i++)
	{
		x[0][i + 1] = x[0][i] - 9;
		y[0][i + 1] = y[0][i] + 7;
		x[1][i + 1] = x[1][i] + 9;
		y[1][i + 1] = y[1][i] + 7;
		x[2][i + 1] = x[2][i] + 9;
		y[2][i + 1] = y[2][i] - 7;
		x[3][i + 1] = x[3][i] - 9;
		y[3][i + 1] = y[3][i] - 7;
	}
	for (int j = 0; j <= 3; j++)
	{
		for (int i = 0; i < MAXATTACKCOUNT; i++)
		{
			attack_xy = dm.FindNearestPos(result_posx[j], 1, x[j][i], y[j][i]);
			x[j][i] = _ttoi(attack_xy.Left(3));
			y[j][i] = _ttoi(attack_xy.Right(3));
			if (false == IsThreadRun) return -1;
		}
		if (false == IsThreadRun) return -1;
	}
	SetLog(_T("定位完成"), true, BLUECOLOR, false);
	Delay(200);
	GetArmyMsg();
	VARIANT xg, yg;
	for (int j = 0; j <= 3; j++)
	{
		if (false == IsThreadRun) return -1;

		//giant
		solider_num = SelectSolider(GIANT);

		if (solider_num > 0)
		{
			//distance = MAXATTACKCOUNT / (solider_num / (4 - j) + 1);
			// distance*count=ldis
			distance = army_capacity / 4 / AVOID_ZERO(solider_num / (4 - j));
			Delay(100);
			for (int i = distance; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Delay(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Delay(AttackChangeDelay);
		solider_num = SelectSolider(BARBARIN);
		if (solider_num > 0)
		{
			distance = army_capacity / 4 / AVOID_ZERO(solider_num / (4 - j));
			Delay(100);
			for (int i = 1; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Delay(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Delay(AttackChangeDelay);
		solider_num = SelectSolider(WALLBREAKER);
		if (solider_num > 0)
		{
			distance = army_capacity / 4 / AVOID_ZERO(solider_num / (4 - j));
			Delay(100);
			for (int i = 1; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Delay(AttackSpeed);
				dm.LeftClick();
			}
		}
		Delay(AttackChangeDelay);
		//goblin
		solider_num = SelectSolider(GOBLIN);
		if (solider_num > 0)
		{
			distance = army_capacity / 4 / AVOID_ZERO(solider_num / (4 - j));
			Delay(100);
			for (int i = 1; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Delay(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Delay(AttackChangeDelay);
		//archer
		solider_num = SelectSolider(ARCHER);
		if (solider_num > 0)
		{
			distance = army_capacity / 4 / AVOID_ZERO(solider_num / (4 - j));
			Delay(100);
			for (int i = 1; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Delay(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		solider_num = SelectSolider(WIZARD);
		if (solider_num > 0)
		{
			distance = army_capacity / 4 / AVOID_ZERO(solider_num / (4 - j));
			Delay(100);
			for (int i = 1; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Delay(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		if (scriptInfo <= 0)
		{

			return 0;
		}
		dm.FindMultiColor(25, 570, 827, 652, "84bce0-0f0f0f", "-26|22|5f97ce-0f0f0f,27|24|6297cc-0f0f0f,-11|45|4b6e8f-0f0f0f,17|42|4a6f95-0f0f0f", 0.9, 1, &xg, &yg);//释放 援军
		if (xg.lVal > 0)
		{
			SetLog("释放援军", true, BLUECOLOR, false); dm.MoveTo(xg.lVal, yg.lVal); Delay(20); dm.LeftClick(); Delay(200); dm.MoveTo(x[0][1], y[0][1]); Delay(20); dm.LeftClick();
		}
		dm.FindMultiColor(18, 568, 834, 617, "e7b463-0f0f0f", "21|13|e8a540-0f0f0f,-7|13|e0bf76-0f0f0f,4|9|e89268-0f0f0f,8|10|ea946e-0f0f0f", 0.9, 1, &xg, &yg);//bar barin king
		if (xg.lVal > 0)
		{
			SetLog("释放蛮王", true, BLUECOLOR, false); dm.MoveTo(xg.lVal, yg.lVal); Delay(20); dm.LeftClick(); Delay(200); dm.MoveTo(x[0][1], y[0][1]); Delay(20); dm.LeftClick();
		}

		dm.FindMultiColor(18, 568, 834, 617, "6C4CB4-040404", "0|0|6C4CB4-040404,4|-1|7253BC-060704,-8|16|D59486-0B1012,7|15|E48A61-040202,8|12|F39A6E-030503,11|12|F4A074-040404,23|13|6C44B6-040202,26|21|6840B0,31|21|6C48BB-040303", 0.9, 1, &xg, &yg);//archer king
		if (xg.lVal > 0)
		{
			SetLog("释放女王", true, BLUECOLOR, false);
			dm.MoveTo(xg.lVal, yg.lVal);
			Delay(20);
			dm.LeftClick();
			Delay(200);
			dm.MoveTo(x[0][1], y[0][1]);
			Delay(20);
			dm.LeftClick();
		}
		dm.FindMultiColor(18, 568, 834, 617, GRAND_WARDEN_COLOR1, GRAND_WARDEN_COLOR2, 0.9, 0, &xg, &yg);
		if (xg.lVal > 0)
		{
			SetLog("守护者", true, BLUECOLOR, false);
			dm.MoveTo(xg.lVal, yg.lVal);
			Delay(20);
			dm.LeftClick();
			Delay(200);
			dm.MoveTo(x[0][1], y[0][1]);
			Delay(20);
			dm.LeftClick();
		}
		Delay(AttackChangeDelay);
	}
	SetLog("释放剩余兵种", true, BLUECOLOR, false);
	for (int j = 0; j <= 3; j++)
	{
		if (false == IsThreadRun) return -1;
		//giant
		solider_num = SelectSolider(GIANT);
		if (solider_num > 0)
		{
			Delay(100);
			for (int i = 0; i < solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Delay(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Delay(AttackChangeDelay);
		solider_num = SelectSolider(BARBARIN);
		if (solider_num > 0)
		{
			Delay(50);
			for (int i = 0; i <= 20; i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Delay(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Delay(AttackChangeDelay);
		solider_num = SelectSolider(WALLBREAKER);
		if (solider_num > 0)
		{
			Delay(100);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Delay(AttackSpeed);
				dm.LeftClick();
			}
		}
		Delay(AttackChangeDelay);
		//goblin
		solider_num = SelectSolider(GOBLIN);
		if (solider_num > 0)
		{
			Delay(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Delay(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Delay(AttackChangeDelay);
		//archer
		solider_num = SelectSolider(2);
		if (solider_num > 0)
		{
			Delay(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Delay(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		if (false == IsThreadRun) return -1;
		dm.FindMultiColor(25, 570, 827, 652, "84bce0-0f0f0f", "-26|22|5f97ce-0f0f0f,27|24|6297cc-0f0f0f,-11|45|4b6e8f-0f0f0f,17|42|4a6f95-0f0f0f", 0.9, 1, &xg, &yg);//释放 援军
		if (xg.lVal > 0)
		{
			SetLog("释放援军", true, BLUECOLOR, false); dm.MoveTo(xg.lVal, yg.lVal); Delay(20); dm.LeftClick(); Delay(200); dm.MoveTo(x[0][1], y[0][1]); Delay(20); dm.LeftClick();
		}
		dm.FindMultiColor(18, 568, 834, 617, "e7b463-0f0f0f", "21|13|e8a540-0f0f0f,-7|13|e0bf76-0f0f0f,4|9|e89268-0f0f0f,8|10|ea946e-0f0f0f", 0.9, 1, &xg, &yg);//bar barin king
		if (xg.lVal > 0)
		{
			SetLog("释放蛮王", true, BLUECOLOR, false); dm.MoveTo(xg.lVal, yg.lVal); Delay(20); dm.LeftClick(); Delay(200); dm.MoveTo(x[0][1], y[0][1]); Delay(20); dm.LeftClick();
		}

		dm.FindMultiColor(18, 568, 834, 617, "6C4CB4-040404", "0|0|6C4CB4-040404,4|-1|7253BC-060704,-8|16|D59486-0B1012,7|15|E48A61-040202,8|12|F39A6E-030503,11|12|F4A074-040404,23|13|6C44B6-040202,26|21|6840B0,31|21|6C48BB-040303", 0.9, 1, &xg, &yg);//archer king
		if (xg.lVal > 0)
		{
			SetLog("释放女王", true, BLUECOLOR, false);
			dm.MoveTo(xg.lVal, yg.lVal);
			Delay(20);
			dm.LeftClick();
			Delay(200);
			dm.MoveTo(x[0][1], y[0][1]);
			Delay(20);
			dm.LeftClick();
		}
		Delay(AttackChangeDelay);
	}

	Delay(2000);

	return 0;
}


int CScript::SetLog(CString logStr, bool IsShow, COLORREF color, bool IsSave)
{
	//如果父窗口句柄为空，则不发送
	if (hParennt == NULL) return -1;
	//消息结构体
	SEND_INFO info = { logStr,IsShow,color,IsSave };
	//向主窗口发送日志消息
	::SendMessage(hParennt, TH_SETLOG, AppPlayerIndex, (LPARAM)&info);
	return 0;
}


int CScript::Attack_lua()
{
	/*调用lua脚本*/
	glua[AppPlayerIndex].call_script(coc.getSets("AttackLuaName"));
	return 0;
}


int CScript::CheckDeadbase()
{
	VARIANT x, y;
	int ElixirType = 0;
	ElixirType = _ttoi(coc.getSets("SearchDeadbaseElixir"));
	int result = -1;
	CString str_i, deadbase_pic;
	if (townLevel >= 7)
	{
		dm.SetPath(_T("\\Pic\\normal\\deadbase"));
		str_i = "d_*.bmp";
		switch (ElixirType)
		{
		case 0:
			str_i = "d_*.bmp";
			break;
		case 1:
			str_i = "*75*.bmp|*100*.bmp";
			break;
		case 2:
			str_i = "*100*.bmp";
			break;
		default:
			str_i = "d_*.bmp";

		}
		deadbase_pic = dm.MatchPicName(str_i);
		dm.FindPic(30, 30, 800, 620, deadbase_pic, "0f0f0f", 0.89, 0, &x, &y);
		if (x.lVal > 0)
			result = 1;


	}
	else
	{
		dm.SetPath(_T("\\Pic\\weak\\deadbase"));

		str_i = "d_*.bmp";
		deadbase_pic = dm.MatchPicName(str_i);

		dm.FindPic(30, 30, 800, 620, deadbase_pic, "0f0f0f", 0.85, 0, &x, &y);
		if (x.lVal > 0)
		{
			result = 1;
		}


	}
	if (result == 1)
	{
		if (townLevel >= 10)
		{
			str_i = dm.FindColorBlockEx(30, 30, 800, 620, "a7b052-050f0f|9cb24a-050f0f|bad058-050f0f|adbc52-050f0f", 1, 30, 6, 6);
			int count = dm.GetResultCount(str_i);
			str_i.Format("attack count:%d", count);
			SetLog(str_i);
			result = count < 100 ? 0 : 1;
		}
	}
	return result;
}


int CScript::CheckDefends()
{
	dm.SetPath(_T("\\Pic\\normal\\defends"));
	int IsTooHigh = 0;
	CString str;
	CString match_str, leftStr;
	int defendType[10] = { 0 };
	defendType[0] = _ttoi(coc.getSets("ArcherTower"));
	defendType[1] = _ttoi(coc.getSets("Mortar"));
	defendType[2] = _ttoi(coc.getSets("WizardTower"));
	defendType[3] = _ttoi(coc.getSets("AirDefense"));
	defendType[4] = _ttoi(coc.getSets("XBow"));
	defendType[5] = _ttoi(coc.getSets("Inferno"));
	defendType[6] = _ttoi(coc.getSets("EagleArtillery"));
	int defendLevel[10] = { 0 };
	defendLevel[0] = _ttoi(coc.getSets("ArcherTowerLevel")) + 1;
	defendLevel[1] = _ttoi(coc.getSets("MortarLevel")) + 1;
	defendLevel[2] = _ttoi(coc.getSets("WizardTowerLevel")) + 1;
	defendLevel[3] = _ttoi(coc.getSets("AirDefenseLevel")) + 1;
	defendLevel[4] = _ttoi(coc.getSets("XBowLevel")) + 1;
	defendLevel[5] = _ttoi(coc.getSets("InfernoLevel")) + 1;
	defendLevel[6] = _ttoi(coc.getSets("EagleArtilleryLevel")) + 1;
	CString strDefendName[8] = {};
	CString PicName;
	strDefendName[0] = "ArcherTower";
	strDefendName[1] = "Mortar";
	strDefendName[2] = "WizardTower";
	strDefendName[3] = "AirDefense";
	strDefendName[4] = "XBow";
	strDefendName[5] = "Inferno";
	strDefendName[6] = "EagleArtillery";

	PicName = dm.MatchPicName("*.bmp");

	match_str = dm.FindPicExS(0, 0, 840, 650, PicName, "0f0f0f", 0.9, 0);
	if (match_str.GetLength() > 3)
	{
		for (int i = 0; i < 7; i++)
		{
			if (defendType[i] == 1)
			{
				for (int j = defendLevel[i]; j < 15; j++)
				{
					str.Format("_lv%d", j);
					str = strDefendName[i] + str;
					if (match_str.Find(str) >= 0)
					{
						IsTooHigh = 1;
						break;
					}
				}
				if (IsTooHigh)
				{
					break;
				}

			}
		}


	}
	return IsTooHigh;
}


int CScript::SearchResult(long InputGold, long IputElixir, long gold, long Elixir, int type)
{
	switch (type)
	{
	case 0:
		if ((gold + Elixir) >= (InputGold + IputElixir))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case 1:
		if (gold >= InputGold&&Elixir >= IputElixir)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case 2:
		if (gold >= InputGold || Elixir >= IputElixir)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
	return 0;
}


int CScript::SearchFish()
{
	SetLog(_T("搜鱼"), true, BLUECOLOR, false);
	LeftClick(63, 610, 200);// 点击进攻按钮
	Delay(2000);
	LeftClick(675, 413, 200);// 点击搜索按钮
	Delay(200);

	const int maxStrLen = 7;
	int search_i = 0;
	int type = 0;
	int fight_value = 0;
	long SearchCount = 0;
	long SearchMaxCount = 0;
	int DeBugSearchShoot = 0;
	CString str1, str2, str3, G_gold, G_water, G_oil;
	CString showStr;
	str1 = coc.getSets("SearchMinGold");
	str2 = coc.getSets("SearchMinElixir");
	str3 = coc.getSets("SearchMinDarkElixir");
	SearchMaxCount = _ttoi(coc.getSets("SearchMaxCount"));
	DeBugSearchShoot = _ttoi(coc.getSets("DeBugSearchShoot"));
	type = _ttoi(coc.getSets("SearchType"));
	long SearchDelay = _ttoi(coc.getSets("SearchDelay")) * 1000;
	long SearchWait = _ttoi(coc.getSets("SearchWait")) * 5;
	int OnlySearch = _ttoi(coc.getSets("OnlySearch"));
	if (SearchWait / 5 < 20)
	{
		SearchWait = 20 * 5;
	}
	long T_gold = _ttoi(str1), T_water = _ttoi(str2), T_oil = _ttoi(str3);
	VARIANT x, y;
	do
	{
		SearchCount++;
		if (SearchCount > SearchMaxCount) {
			showStr.Format("搜索次数超过%d", SearchMaxCount);
			return 0;
		}
		LootRecord[SwitchNo].SearchCount++;
		search_i = 0;
		do
		{
			if (scriptInfo <= 0)
			{
				return 0;
			}
			dm.FindMultiColor(702, 481, 840, 544, "f0b028-0f0f0f", "71|-4|f0b028-0f0f0f,3|31|d84d00-0f0f0f,87|34|d84800-0f0f0f",
				0.9, 0, &x, &y);
			if (search_i >= SearchWait)
			{
				SetLog(_T("卡白云时间过长！尝试重新启动"), true, REDCOLOR, false);
				scriptInfo = -2;
				return 0;
			}
			search_i = search_i + 1;
			Delay(200);
		} while (x.lVal < 0);
		Delay(100);
		Delay(SearchDelay);
		dm.UseDict(1);
		G_gold = dm.Ocr(46, 65, 121, 84, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.8);
		G_water = dm.Ocr(44, 96, 121, 114, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.8);
		G_oil = dm.Ocr(44, 117, 113, 145, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.8);
		showStr.Format("No.[%ld] 金币[%s] 圣水[%s] 黑油[%s]", SearchCount,
			G_gold, G_water, G_oil);
		SetLog(showStr, true, BLACKCOLOR, false);
		if (SearchResult(T_gold, T_water, _ttoi(G_gold), _ttoi(G_water), type) > 0
			&& _ttoi(G_oil) >= T_oil)
		{
			if (OnlySearch == 1) {
				Notify();
				SetLog(_T("搜索到大鱼，手动进攻"), true, BLUECOLOR, false);
				return 1;
			}
			if (CheckDeadbase() == 1)
			{
				fight_value = 1;
				if (CheckDefends() >= 1)
				{
					fight_value = 0;
					dm.MoveTo(767, 517);
					Delay(200);
					dm.LeftClick();
					SetLog(_T("防御过高"), true, BLUECOLOR, false);
					Delay(1000);
				}
			}
			else
			{
				if (DeBugSearchShoot == 1)
				{
					dm.SetPath("\\Debug\\Search");
					showStr.Format("%ld", SearchCount);
					dm.Capture(0, 0, 840, 650, showStr + ".bmp");
				}
				fight_value = 0;
				dm.MoveTo(767, 517);
				Delay(200);
				dm.LeftClick();
				SetLog(_T("不是死鱼"), true, BLUECOLOR, false);
				Delay(1000);
			}
		}
		else
		{
			fight_value = 0;
			dm.MoveTo(767, 517);
			Delay(200);
			dm.LeftClick();
			Delay(1000);
		}
		if (false == IsThreadRun)
		{
			return 0;
		}
	} while (fight_value != 1);
	if (false == IsThreadRun)
	{
		return 0;
	}
	return 1;
}


void CScript::CollectResource()
{
	SetLog("收集资源", true, BLUECOLOR, false);
	VARIANT x, y;
	// 点一次就可以收集所有的了
	for (int s = 1; s < 2; s++)
	{
		dm.FindMultiColor(74, 51, 734, 603, "d8dcb8-050808",
			"15|1|d8dcb8-050808, 5|10|403048, 8|11|4b3854-050808, -3|13|b8c088,16|13|b8c088-050505",
			0.9, 0, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Delay(20);
			dm.LeftClick();
			Delay(100);
		}
		Delay(60);
	}
	Delay(500);
	for (int s = 1; s < 2; s++)
	{
		//dm.FindPic(75, 41, 680, 528, "gold.bmp", "0f0f0f", 0.9, 0, &x, &y);
		dm.FindMultiColor(74, 51, 734, 603, "d6dcb8-050808", 
			"16|2|d0dbb8-050808,6|4|f031d8-080808,9|4|ef35df-090909,5|9|d653c8-090909,7|10|df58d0-090909",
			0.9, 0, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Delay(20);
			dm.LeftClick();
			Delay(100);
		}
		Delay(60);
	}
	Delay(500);
	for (int s = 1; s < 2; s++)
	{
		//dm.FindPic(75, 41, 680, 528, "darkelixir.bmp", "0f0f0f", 0.9, 0, &x, &y);
		dm.FindMultiColor(74, 51, 734, 603, "d3dcb8-090909", 
			"15|0|d4dcb8-090909,5|5|ffe848-090909,6|5|ffed48-090909,9|5|ffe418-090909",
			0.9, 0, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Delay(20);
			dm.LeftClick();
			Delay(200);
		}
	}
	Delay(1000);
}


int CScript::DonateArmy()
{
	if (_ttoi(coc.getSets("DonateArmy")) != 1) return -1;
	SetLog("捐兵", true, BLUECOLOR, false);
	int DonateType = 0;
	int ret = 0;
	DonateType = _ttoi(coc.getSets("DonateType"));
	int should_donate = 0;
	long FindY = 0;
	//1.设置字库
	dm.SetPath("\\Pic\\others\\DonateArmy");
	dm.UseDict(DICT_COC_DONATE);
	VARIANT x, y;
	long fx = 0, fy = 0;
	//2.>> button
	dm.FindMultiColor(3, 297, 40, 393, "f09c11-0f0f0f", "11|14|e8882a-0f0f0f,5|26|ffffff-0f0f0f,3|50|bb4808-0f0f0f", 1.0, 1, &x, &y);//>> button
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Delay(20);
		dm.LeftClick();
	}
	else
	{
		SetLog("not find >> button");
		return -1;
	}
	//3.需要设置的

	int IsArmy[21] = { 1 };
	IsArmy[0] = _ttoi(coc.getSets("IsBarbarin"));
	IsArmy[1] = _ttoi(coc.getSets("IsArcher"));
	IsArmy[2] = _ttoi(coc.getSets("IsGiant"));
	IsArmy[3] = _ttoi(coc.getSets("IsGoblin"));
	IsArmy[4] = _ttoi(coc.getSets("IsWallBreaker"));
	IsArmy[5] = _ttoi(coc.getSets("IsBallon"));
	IsArmy[6] = _ttoi(coc.getSets("IsWizard"));
	IsArmy[7] = _ttoi(coc.getSets("IsHealer"));
	IsArmy[8] = _ttoi(coc.getSets("IsDragon"));
	IsArmy[9] = _ttoi(coc.getSets("IsPeka"));
	IsArmy[10] = _ttoi(coc.getSets("IsBabyDragon"));
	IsArmy[11] = _ttoi(coc.getSets("IsMiner"));
	IsArmy[12] = _ttoi(coc.getSets("IsMinion"));
	IsArmy[13] = _ttoi(coc.getSets("IsHogRider"));
	IsArmy[14] = _ttoi(coc.getSets("IsValkyrie"));
	IsArmy[15] = _ttoi(coc.getSets("IsGolem"));
	IsArmy[16] = _ttoi(coc.getSets("IsWitch"));
	IsArmy[17] = _ttoi(coc.getSets("IsLavaHound"));
	IsArmy[18] = _ttoi(coc.getSets("IsBower"));
	IsArmy[19] = 1;
	IsArmy[20] = 1;
	//这里设置两个矩阵
	//意愿矩阵和识别矩阵

	int WantDonate[21] = { 1 };
	int NeedDonate[21] = { -1 };
	CString donateStr;//捐兵的字符串
	CString donateX, donateY;
	VARIANT xs, ys;
	CString str;
	char buffer[512] = { 0 };
	using namespace std;
	vector<string> vstr1, vstr2;
	long lastY = 84;
	long y1, y2;
	y1 = y2 = 0;
	Delay(2000);
	//4.寻找“增援”按钮
	//捐助按钮
	for (lastY = 84; lastY < 660; )
	{
		dm.FindMultiColor(189, lastY, 306, 660, "cced74-090509", "33|-4|d5f27d-090509,62|-3|d5f17d-090509,1|15|75bf2d-080804,32|17|6db72d-080804,57|16|6ebc2d-080804", 1.0, 0, &x, &y);
		//6.ocr
		fx = x.lVal;
		fy = y.lVal;
		if (fx <= 0)
		{
			lastY += 60;
			continue;
		}
		else
		{
			lastY = fy;
		}
		y1 = fy - 40, y2 = fy + 30;
		donateStr = dm.Ocr(9, y1, 283, y2, "bfc1bf-0f0f0f|f5f5f5-0f0f0f|d7d7d7-0f0f0f|9b9d9b-0f0f0f", 0.85);
		if (donateStr.GetLength() > 0)
		{
			SetLog(_T("需要:") + donateStr, true, BLUECOLOR, false);
		}
		else
		{
			continue;
		}
		//7.查找,并赋值给需求矩阵
		if (DonateType != 2)
		{
			for (int j = 0; j < 21; j++)
			{
				NeedDonate[j] = donateStr.Find(ARMYNAME[j]) + 1;
			}
		}




		//8.点击 “增援”
		dm.MoveTo(fx, fy);
		Delay(20);
		dm.LeftClick();
		Delay(2000);
		//find small red x
		dm.FindMultiColor(716, 3, 760, 663, "ffffff", "19|1|cd151d-050505,35|4|ffffff", 1.0, 1, &x, &y);
		if (x.lVal > 0)
		{
		}
		else
		{
			SetLog("not find small red x");
			continue;
		}
		int y0 = y.lVal + 10;
		int n = 0;
		//9.寻找兵图标 并点击

		switch (DonateType)
		{
		case 0:
			for (n = 0; n < 21; n++)
			{
				if (WantDonate[n] * NeedDonate[n] <= 0) continue;
				if (DonateClick(n, 8, y0) == 1) break;
			}
			break;
		case 1:
			for (n = 0; n < 21; n++)
			{
				if (WantDonate[n] <= 0) continue;
				if (DonateClick(n, 8, y0) == 1) break;
			}
			break;
		case 2:
			for (n = 0; n < 21; n++)
			{

				str.Format("UserWant %d", n);
				GetPrivateProfileString("捐兵/请求", str, "", buffer, 512, coc.GetPath());
				if (strlen(buffer) == 0) continue;
				_split(buffer, vstr1, "|");
				if (vstr1.size() < 2) continue;
				WantDonate[n] = _ttoi(vstr1[0].c_str());
				if (WantDonate[n] != 1) continue;
				if (vstr1[1].length() == 0) continue;
				_split(vstr1[1], vstr2, ",");
				for (size_t index = 0; index < vstr2.size(); index++)
				{
					NeedDonate[index] = donateStr.Find(vstr2[index].c_str()) + 1;
				}
				if (WantDonate[n] * NeedDonate[n] <= 0) continue;
				if (DonateClick(n, 8, y0) == 1) break;
			}


			break;
		}



		if (false == IsThreadRun)	return 1;

		//10.close .find small red x
		dm.FindMultiColor(716, 3, 760, 663, "ffffff", "19|1|cd151d-050505,35|4|ffffff", 1.0, 1, &x, &y);
		if (x.lVal > 0)
		{

			LeftClick(735, y.lVal);
		}
		Delay(1500);
	}

	dm.FindMultiColor(714, 1, 764, 537, "ffffff-0f0f0f", "-6|-1|f88088-0f0f0f,1|17|ffffff-0f0f0f", 0.9, 1, &x, &y);
	dm.MoveTo(x.lVal, y.lVal);
	Delay(20);
	dm.LeftClick();
	Delay(2000);
	dm.MoveTo(333, 346);
	Delay(20);
	dm.LeftClick();
	return 0;
}


int CScript::IdentifyIsDonate(int* array, int type /* = 2 */)
{
	return -1;
}

int CScript::UpGradeWall()
{
	if (_ttoi(coc.getSets("UpgradeWall")) != 1) return-1;
	dm.SetPath(_T("\\Pic\\normal\\wall"));
	long UpgradeWallMinGold = _ttoi(coc.getSets("UpgradeWallMinGold"));
	long UpgradeWallMinElixir = _ttoi(coc.getSets("UpgradeWallMinElixir"));
	int UpgradeWallUseType = _ttoi(coc.getSets("UpgradeWallUseType"));
	int UpgradeWallLevel = _ttoi(coc.getSets("UpgradeWallLevel"));
	bool IsUpGrade = false;
	VARIANT x, y;
	CString wallPicName;
	CString str, buttonStr, wallPoint;
	switch (UpgradeWallUseType)
	{
	case 0:
		if (LootRecord[SwitchNo].NowGold >= UpgradeWallMinGold)
		{
			buttonStr.Format("upgrade_%d*.bmp", 1);
			IsUpGrade = true;
		}
		break;
	case 1:
		if (LootRecord[SwitchNo].NowElixir >= UpgradeWallMinElixir)
		{
			buttonStr.Format("upgrade_%d*.bmp", 2);
			IsUpGrade = true;
		}
		break;
	case 2:
		if (LootRecord[SwitchNo].NowDarkElixir >= UpgradeWallMinElixir || LootRecord[SwitchNo].NowGold >= UpgradeWallMinGold)
		{
			buttonStr = "upgrade*.bmp";
			IsUpGrade = true;
		}
		break;
	default:
		break;
	}
	if (false == IsUpGrade)
	{
		return 0;
	}


	if (UpgradeWallLevel == 0)
	{
		str = "wall_*.bmp";
	}
	else
	{
		str.Format("wall_%d*.bmp", UpgradeWallLevel);
	}
	wallPicName = dm.MatchPicName(str);//获取城墙图片
	using std::vector;
	using std::string;
	vector<string> help, strHelp;
	wallPoint = dm.FindPicExS(30, 30, 830, 640, wallPicName, "0f0f0f", 0.9, 2);
	if (wallPoint.GetLength() <= 0)
	{
		return 0;
	}
	_split(wallPoint.GetBuffer(), help, "|");
	wallPoint.ReleaseBuffer();
	for (size_t i = 0; i < help.size(); i++)
	{
		str = help[i].c_str();
		SetLog(str);
		_split(help[i], strHelp, ",");
		dm.MoveTo(_ttoi(strHelp[1].c_str()), _ttoi(strHelp[2].c_str()));
		Delay(20);
		dm.LeftClick();
		Delay(500);
		for (int j = 0; j < 10; j++)
		{
			dm.FindMultiColor(357, 523, 432, 552, "ffffb7-050f0f", "0|2|ffffb7-05090f,-1|3|f9f9b4-05090f,0|3|ffffb7-05090f,1|3|faf9b6-05090f,0|7|ffffb7-05090f,4|2|ffffb7-05090f,4|6|fefeb8-05090f,6|1|eae59b-05090f", 0.9, 0, &x, &y);
			if (x.lVal > 0)
			{
				SetLog("find wall");
				dm.FindPic(391, 550, 624, 577, dm.MatchPicName(buttonStr), "0f0f0f", 0.85, 0, &x, &y);
				if (x.lVal > 0)
				{
					dm.MoveTo(x.lVal, y.lVal);
					Delay(20);
					dm.LeftClick();
					Delay(1000);
					dm.FindPic(352, 474, 537, 507, dm.MatchPicName(buttonStr), "0f0f0f", 0.85, 0, &x, &y);
					if (x.lVal > 0)
					{
						dm.MoveTo(x.lVal, y.lVal);
						Delay(20);
						dm.LeftClick();
						return 1;
						break;
					}
				}
			}
			else
			{
				Delay(100);
			}
		}

		if (i > 5)
		{
			break;
		}
	}
	return 0;


}


int CScript::ConnectAppPlayer()
{
	int BindInfo = 0;
	long IsBind = 0;
	CString str;
	CString bindstr[5] = { "" };
	//****************** check and bind ****************//
	switch (AppPlayerType)
	{
	case APP_PLAYER_BLUESTACKS:
		//window_hwnd = dm.FindWindow("", "BlueStacks App Player");
		bindstr[0] = "gdi2";
		bindstr[1] = "windows";
		bindstr[2] = "windows";
		bindstr[3] = "";
		bindstr[4] = "0";
		break;
	case APP_PLAYER_LIGHTING:
		bindstr[0] = "dx.graphic.opengl";
		bindstr[1] = "windows";
		bindstr[2] = "windows";
		bindstr[3] = "";
		bindstr[4] = "4";
		break;
	default:
		BindInfo = -2;
		break;
	}
	if (bindHwnd > 0)
	{
		IsBind = dm.BindWindowEx(bindHwnd, bindstr[0], bindstr[1],
			bindstr[2], bindstr[3], _ttoi(bindstr[4]));
		if (IsBind == 1)
		{
			BindInfo = 1;
			str = "成功连接模拟器";
			SetLog(str);
		}
		else
		{
			BindInfo = -1;
			str.Format("连接模拟器失败 GetLastError=%ld", dm.GetLastError());
			SetLog(str, true, REDCOLOR, true);
			AfxMessageBox(str, MB_OK);
		}
	}
	else
	{
		BindInfo = -2;//no hwnd
	}
	return BindInfo;//-1:Bind False ,-2,No Hwnd
}


int CScript::SetAppResolution(int x, int y)
{
	CString path;
	path = coc.GetCurrentPath();
	path += "Config.ini";
	const int max_size = 512;
	char buffer[max_size] = { 0 };
	VARIANT xw, yw;
	CString str;
	CRegKey key;
	DWORD w = x;
	DWORD h = y;
	dm.GetClientSize(bindHwnd, &xw, &yw);
	if ((xw.lVal != APP_RESOLUTION_X) || (yw.lVal != APP_RESOLUTION_Y))
	{
		str.Format("错误的分辨率：%ld,%ld，关闭模拟器再设置新的分辨率", xw.lVal, yw.lVal);
		SetLog(str, true, BLUECOLOR, false);
		QuitAppPlayer(AppPlayerIndex);
		Delay(3000);
	}
	else
	{
		return 0;
	}
	switch (AppPlayerType)
	{
	case APP_PLAYER_BLUESTACKS:
		key.Create(HKEY_LOCAL_MACHINE, 
			_T("SOFTWARE\\BlueStacks\\Guests\\Android\\FrameBuffer\\0"));
		key.SetDWORDValue(_T("Width"), w);
		key.SetDWORDValue(_T("Height"), h);
		key.SetDWORDValue(_T("GuestWidth"), w);
		key.SetDWORDValue(_T("GuestHeight"), h);
		key.SetDWORDValue(_T("WindowWidth"), w);
		key.SetDWORDValue(_T("WindowHeight"), h);
		key.Close();
		break;
	case APP_PLAYER_LIGHTING:
		str.Format("\\dnconsole.exe modify --index %d --resolution %d,%d,160"
			" --cpu 1 --memory 1024", AppPlayerIndex,
			APP_RESOLUTION_X, APP_RESOLUTION_Y);
		adb.start(appPlayerInstallDir + str);
		adb.stop();
		break;
	default:
		break;
	}
	return 1;
}


int CScript::StartCoc()
{
	CString cocVer, str;
	str.Format("%d", AppCocID);
	char buffer[128] = { 0 };
	GetPrivateProfileString("version", str, "", buffer, 128,
		GetCurrentPath() + "CocVersion.ini");
	TRACE("start coc %d %s\n", AppCocID, buffer);
	adbRunApp(buffer);
	SetLog("启动部落冲突", true, BLUECOLOR, false);
	return 0;
}


int CScript::StopCoc()
{
	CString str;
	str.Format("%d", AppCocID);
	char buffer[128] = { 0 };
	GetPrivateProfileString("version", str, "", buffer, 128,
		coc.GetCurrentPath() + "CocVersion.ini");
	adbCloseApp(buffer);
	SetLog("停止部落冲突", true, BLUECOLOR, false);
	return 0;
}


int CScript::ControlTroophs()
{
	long NowTroophs = LootRecord[SwitchNo].NowTroophs;
	long MaxTroophs = _ttol(coc.getSets("MaxTroophs"));
	if (_ttoi(coc.getSets("ControlTroophs")) == 0 || NowTroophs <= MaxTroophs)
		return 1;

	CString str;
	str.Format("自动降杯（%d > %d）", NowTroophs, MaxTroophs);
	SetLog(str, true, REDCOLOR, false);
	LeftClick(63, 610, 200);// 点击进攻按钮
	Delay(2000);
	LeftClick(675, 413, 200);// 点击搜索按钮
	Delay(200);

	VARIANT x, y;
	int search_i = 0;
	long SearchCount = 0;
	CString str1, str2, str3, G_gold, G_water, G_oil, SearchCount_str;
	long SearchWait = _ttol(coc.getSets("SearchWait")) * 5;
	SearchCount++;
	search_i = 0;
	do
	{
		if (scriptInfo <= 0)
		{
			return 0;
		}
		dm.FindMultiColor(702, 481, 840, 544, 
			"f0b028-0f0f0f", "71|-4|f0b028-0f0f0f,3|31|d84d00-0f0f0f,87|34|d84800-0f0f0f",
			0.9, 0, &x, &y);
		if (search_i >= SearchWait)
		{
			SetLog(_T("卡白云时间过长！尝试重新启动"), true, REDCOLOR, false);
			StopCoc();
			scriptInfo = ShouldRestart;
			return 0;
		}
		search_i = search_i + 1;
		Delay(200);
	} while (x.lVal < 0);
	Delay(100);

	int i;
	for (i = 1; i <= 3; i++)
	{
		if (SelectHero(i) != 0)
		{
			LeftClick(7, 305, 20); // 点击进攻位置，最做左面边缘
			Delay(500);
			break;
		}
	}
	if (i > 3) {
		SetLog("没有可用的英雄", true, REDCOLOR, false);
		return 1;
	}
	LeftClick(54, 533, 20); // 结束战斗
	Delay(1000);
	LeftClick(515, 387, 20); // 确定
	Delay(500);
	LeftClick(426, 528, 20); // 回营
	Delay(3000);
	return 0;
}


int CScript::ZoomOut()
{
	const int Ctrl = 17;
	int n = 0;
	AppPlayerType == APP_PLAYER_LIGHTING ? n = 3 : n = 10;
	for (int i = 1; i <= n; i++)
	{
		if (IsThreadRun == false)
		{
			return 0;
		}
		dm.KeyPress(40);
		Delay(100);
	}
	adbSwipe(400, 100, 400, 600);
	return 1;
}


bool CScript::HideKey()
{
	return false;
}


int CScript::AddDict()
{
	long ret = 0;
	dm.SetPath("\\Dict");
	ret += dm.SetDict(DICT_COC_ARMY, "coc_army.bak"); //设置字库 0
	ret += dm.SetDict(DICT_COC_FISH, "cocfish.txt");      //设置字库 1
	ret += dm.SetDict(DICT_COC_RESOURCE, "cocresource.bak");  //设置字库 2
	ret += dm.SetDict(DICT_COC_TROOPTH, "cocbein.bak");      //设置字库 3
			//dm.SetDict(4, "OnlineTime.txt");   //设置字库 4
	ret += dm.SetDict(DICT_COC_DONATE, "coc_donate.txt");   //设置字库 5
	ret += dm.SetDict(DICT_COC_ATTACKARMY, "AttackArmy.txt");
	return ret;
}


int CScript::RepairAttackArmy(int oldArmyCount, int &distance)
{


	if (oldArmyCount == 0)
	{
		distance = MAXATTACKCOUNT;
	}
	else
	{
		distance = MAXATTACKCOUNT / (oldArmyCount + 2);
	}

	if (distance < 1)
	{
		distance = 1;
	}
	else if (distance > MAXATTACKCOUNT)
	{
		distance = MAXATTACKCOUNT - 2;
	}
	return 0;
}


int CScript::GetArmyMsg()
{
	int type = _ttoi(coc.getSets("attackCount"));
	if (type == 0)//进行识别
	{
		const int minY = 572;
		const int maxY = 597;
		SetLog("识别军队信息：", true, BLUECOLOR, false);
		dm.UseDict(6);
		int x, y;
		long x1 = 0, x2 = 0;
		CString str;
		CString result, first, next, sim;
		CString army_num_str;
		SetPath("\\Pic\\attack\\solider");
		for (int i = 1; i <= ARMY_MAX; i++)
		{
			str.Format("solider_%d.bmp|solider_%d_2.bmp", i, i);
			ImageLoc(25, 570, 833, 650, str, 0.9, x, y);
			x1 = 0, x2 = 0;
			if (x > 0)
			{
				MakeRect(x, &x1, &x2);
				army_num_str = dm.Ocr(x1, minY, x2, maxY, "ffffff-0f0f0f", 0.85);
				if (army_num_str.GetLength() > 0)
				{
					str = ARMYNAME[i - 1];
					str += ":" + army_num_str;
					SetLog(str, true, BLACKCOLOR, false);
					if (army_num_str.Left(1) == "x")
					{
						army_num_str = army_num_str.Right(army_num_str.GetLength() - 1);
					}
					switch (i)
					{
					case BARBARIN:
						attackArmy.babarin = _ttoi(army_num_str);
						break;
					case ARCHER:
						attackArmy.archer = _ttoi(army_num_str);
						break;
					case GIANT:
						attackArmy.giant = _ttoi(army_num_str);
						break;
					case 4:
						attackArmy.goblin = _ttoi(army_num_str);
						break;
					case 5:
						attackArmy.wallbreaker = _ttoi(army_num_str);
						break;
					case 7:
						attackArmy.wizard = _ttoi(army_num_str);
						break;
					default:
						break;
					}
				}
			}
		}
	}
	if (type == 1)//固定为造兵的数量
	{
		return 1;
	}
	return 1;
}


int CScript::MakeRect(long srcX, long* x1, long* x2)
{
	const int minX = 55;
	const int dX = 66;
	const int sX = 4;
	for (int i = minX; i < 850; i = i + dX + sX)
	{
		if ((i <= srcX) && (srcX <= i + dX))
		{
			*x1 = i + 10;
			*x2 = i + dX;
			return 1;
		}
	}
	*x1 = srcX - 30;
	*x2 = srcX + 30;
	return 0;
}


long CScript::WaitPic(long x1, long y1, long x2, long y2, LPCTSTR picName, int timesOut, bool Isclick)
{
	int x, y;
	long result = 0;
	DWORD t1 = GetTickCount();
	do
	{

		ImageLoc(x1, y1, x2, y2, picName, 0.95, x, y);
		Delay(20);

	} while (x <= 0 && GetTickCount() - t1 < timesOut);
	if (x > 0)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	if (Isclick == true && result == 1)
	{
		dm.MoveTo(x, y);
		Delay(20);
		dm.LeftClick();
	}

	return result;
}


int CScript::adbClick(int x, int y)
{
	CString str;
	str.Format("input tap %d %d", x, y);
	adbCmd(str);
	return 0;
}


int CScript::adbSwipe(int x1, int y1, int x2, int y2)
{
	CString str;
	str.Format("input swipe %d %d %d %d", x1, y1, x2, y2);
	adbCmd(str);
	return 0;
}


int CScript::adbKeyEvent(int keyCode)
{
	CString str;
	str.Format("input keyevent %d", keyCode);
	adbCmd(str);
	return 0;
}


int CScript::adbInputText(CString text)
{
	CString buffer = "input text ";
	buffer += text;
	adbCmd(text);
	return 0;
}


int CScript::adbRunApp(CString packageNameAndClassName)
{
	CString str;
	vector<CString> vstr;
	switch (AppPlayerType)
	{
	case APP_PLAYER_BLUESTACKS:
		str = "am start -n ";
		str += packageNameAndClassName;
		adbCmd(str);
		break;
	case APP_PLAYER_LIGHTING:
		Split(packageNameAndClassName, vstr, "/");
		str.Format("\\dnconsole.exe runapp --index %d --packagename %s",
			AppPlayerIndex, vstr[0]);
		TRACE("adbRunApp %s\n", str);
		adb.start(appPlayerInstallDir + str);
		adb.stop();
		break;
	default:
		break;
	}
	return 0;
}


int CScript::adbCloseApp(CString packageNameAndClassName)
{
	CString str;
	vector<CString> vstr;
	Split(packageNameAndClassName, vstr, "/");
	CString packageName = vstr[0];
	TRACE("adbCloseApp packageName %s\n", packageName);
	switch (AppPlayerType)
	{
	case APP_PLAYER_BLUESTACKS:
		str = "am force-stop ";
		str += packageName;
		adbCmd(str);
		break;
	case APP_PLAYER_LIGHTING:
		str.Format("\\dnconsole.exe killapp --index %d --packagename %s",
			AppPlayerIndex, packageName);
		adb.start(appPlayerInstallDir + str);
		adb.stop();
		break;
	default:
		break;
	}
	return 0;
}


int CScript::Statistics()
{
	GetResource();
	if (hParennt == NULL) return -1;
	::SendMessage(hParennt, TH_STASTICS, (WPARAM)&LootRecord[SwitchNo],
		AppPlayerIndex * 3 + SwitchNo);
	return 0;
}


int CScript::DonateClick(int type, int count, int y0)
{
	const long x1 = 322;
	const long x2 = 757;
	CString str;
	dm.SetPath("\\Pic\\others\\DonateArmy");

	str.Format("d%d.bmp", type + 1);
	if (type >= 19)
	{
		str = dm.MatchPicName("d*.bmp");
	}
	VARIANT x, y;
	dm.FindPic(x1, y0, x2, y0 + 210, str, "0f0f0f", 0.9, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Delay(20);
		for (int j = 1; j <= count; j++)
		{
			dm.LeftClick();
			Delay(100);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}


int CScript::checkMainScreen()
{
	checkScreenError();
	Delay(1000);
	int ret = 0;
	VARIANT x, y;

	for (int i = 0; i < 5; i++)
	{
		dm.FindMultiColor(12, 5, 837, 51, "3abded-0f0f0f", "30|-1|37bfed-0f0f0f,786|7|fff655-0f0f0f,796|9|ffec22-0f0f0f", 1.0, 0, &x, &y);
		if (x.lVal > 0)
		{
			ret = 1;
			break;
		}
		if (IsThreadRun == false)
		{
			ret = -1;
		}
		else
		{
			Delay(500);
		}

	}
	return ret;
}


int CScript::checkScreenError()
{
	dm.SetPath(_T("\\Pic\\others\\checkMainScreen"));
	VARIANT x, y;
	CString str;
	//close
	str = dm.MatchPicName("buttonClose*.bmp");
	dm.FindPic(400, 846, 8, 350, str, "0f0f0f", 0.90, 1, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Delay(20);
		dm.LeftClick();
	}
	//<<
	str = dm.MatchPicName("buttonRequest*.bmp");
	dm.FindPic(309, 285, 356, 406, str, "0f0f0f", 0.90, 1, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Delay(20);
		dm.LeftClick();
	}
	//ok
	dm.FindPic(250, 300, 700, 600, "okButton.bmp", "0f0f0f", 0.90, 1, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Delay(20);
		dm.LeftClick();
	}
	//close red x
	const int x1 = 563, y1 = 3, x2 = 846, y2 = 301;
	dm.FindMultiColor(x1, y1, x2, y2, "ff8d95-050505",
		"12|1|ff8d95-050505,21|1|ff8d95-050505,11|11|ffffff-050505,12|11|ffffff-050505,-1|21|ed1115-050505,24|20|eb1115-050505", 0.9, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Delay(20);
		dm.LeftClick();
	}
	//船
	dm.FindMultiColor(490, 3, 802, 222,
		"612028-080808", "0|1|602028-080808,-1|3|5d1e26-080808,-1|5|5c1c24-080808,-1|6|5b1c24-080808", 0.9, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Delay(20);
		dm.LeftClick();
	}
	//回营
	dm.FindMultiColor(12, 560, 112, 650,
		"eeebd6-030706", "67|-2|f1f2d9-030706,17|2|832b18-030706,56|8|c44e2d-030706,31|24|ffad8f-051312,48|22|ffc0a1-051312", 0.9, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Delay(20);
		dm.LeftClick();
	}
	return 0;
}


int CScript::LaunchAppPlayer(int wParam)
{
	CString str;

	switch (AppPlayerType)
	{
	case  APP_PLAYER_BLUESTACKS:
		if (PathFileExists(appPlayerInstallDir))
		{
			ShellExecute(NULL, "open", appPlayerInstallDir + "\\HD-StartLauncher.exe", NULL, NULL, SW_NORMAL);
		}
		else
		{
			AfxMessageBox("PathFile not Exists");
			IsThreadRun = false;
		}


		break;
	case APP_PLAYER_LIGHTING:
		if (PathFileExists(appPlayerInstallDir))
		{
			str.Format(" launch --index %d", wParam);
			adb.start(appPlayerInstallDir + "\\dnconsole.exe" + str);
			adb.stop();
		}
		else
		{
			AfxMessageBox("PathFile not Exists");
			IsThreadRun = false;
		}
		break;
	default:
		break;
	}

	SetLog("打开模拟器", true, BLUECOLOR, false);
	return 1;
}


int CScript::QuitAppPlayer(int wParam)
{
	const int max_size = 512;
	char buffer[max_size] = { 0 };
	CString path, str;
	path = coc.GetCurrentPath();
	path += "Config.ini";
	int ret = 0;
	CString process_name[8] = {};
	switch (AppPlayerType)
	{
	case  APP_PLAYER_BLUESTACKS:
		process_name[0] = "HD-Agent.exe";
		process_name[1] = "HD-BlockDevice.exe";
		process_name[2] = "HD-Frontend.exe";
		process_name[3] = "HD-LogRotatorService.exe";
		process_name[4] = "HD-Network.exe";
		process_name[5] = "HD-Service.exe";
		process_name[6] = "HD-SharedFolder.exe";
		process_name[7] = "HD-UpdaterService.exe";
		for (int i = 0; i < 8; i++)
		{
			str = dm.EnumProcess(process_name[i]);
			if (coc.KillProcessById(_ttoi(str)))
			{
				ret += 1;
			}
		}
		break;
	case APP_PLAYER_LIGHTING:
		if (PathFileExists(appPlayerInstallDir))
		{
			str.Format(" quit --index %d", wParam);
			adb.start(appPlayerInstallDir + "\\dnconsole.exe" + str);
			adb.stop();
		}
		else
		{
			IsThreadRun = false;
		}
		str = adb.get_result();
		if (str.GetLength() <= 4) return 0;
		break;
	default:
		break;
	}
	SetLog("关闭模拟器", true, REDCOLOR, false);
	return ret;
}

int CScript::RestartScript()
{
	int ret = 0;
	SetLog("掉线");
	//1.
	StopCoc();
	//2.
	scriptInfo = SCRIPT_STATE_IN_RUN;
	//3.先解绑窗口，再把之前创建的对象释放了
	dm.UnBindWindow();
	dm.ReleaseDispatch();
	dm = NULL;
	//4.重新创建一个大漠对象
	if (false == CreateDm())
	{
		IsThreadRun = false;
		AfxMessageBox(_T("启动失败，请检查插件是否注册！"), MB_OK);
	}
	//5..检测插件版本
	if (dm.Ver() != DM_VER_5)
	{
		IsThreadRun = false;
		AfxMessageBox(_T("启动失败，插件版本不正确，请检查插件是否注册！"), MB_OK);
		return 0;
	}
	//6..设置错误提示
	dm.SetShowErrorMsg(_ttoi(coc.getSets("SetShowErrorMsg")));
	Delay(500);
	//7..绑定模拟器
	ret = SetBindHwnd();
	if (ret <= 0)
	{
		AfxMessageBox("未发现模拟器，请重启模拟器和辅助");
		IsThreadRun = false;
		return 0;
	}
	ret = ConnectAppPlayer();
	if (ret == -1)
	{
		IsThreadRun = false;
		return 0;
	}
	if (ret == -2)
	{
		SetLog("请检查模拟器是否打开!", true, RGB(0xff, 0x00, 0xff), true);
		IsThreadRun = false;
		return 0;
	}
	Delay(3000);
	//8..添加字库
	AddDict();
	//9.
	StartCoc();
	return 1;
}

int CScript::WaitForTrainArmy()
{
	StopCoc();
	SetLog("等待造兵");
	CString str;
	long st = trainTime * 60;
	do
	{
		str.Format("剩余时间：%dm %ds.", st / 60, st % 60);
		SetLog(str, false, BLUECOLOR, false);
		if (false == IsThreadRun) return-1;
		Delay(1000);
		st--;
	} while (st > 0);
	scriptInfo = SCRIPT_STATE_IN_RUN;
	StartCoc();
	return 0;
}

int CScript::SwitchCoc()
{

	//1.关闭coc
	StopCoc();
	do
	{
		//由于最先运行的是主账号，编号为零，故每次切换，编号增加 1
		SwitchNo += 1;
		//如果超出最大编号，设置成零
		if (SwitchNo >= MAX_SWITCH_COUNT) SwitchNo = 0;
		//如果需切换，则确定为新编号，开始切换
		if (cocInfo[SwitchNo].IsSwitch == true) break;
	} while (IsThreadRun);

	//2.改变配置文件
	coc.SetPath(cocInfo[SwitchNo].configName);
	//3.改变coc 版本编号
	AppCocID = cocInfo[SwitchNo].AppID;
	//4.等等一会 30s
	Delay(30000);
	//5.启动 coc
	StartCoc();
	//6.设置脚本信息为正常
	scriptInfo = SCRIPT_STATE_IN_RUN;
	//结束
	return 0;
}

int CScript::Attack()
{
	int Ret = 0;
	if (_ttoi(coc.getSets("Attack")) != 1) return 0;
	Delay(2000);
	MakeArmy();
	Delay(2000);
	if (IsThreadRun == false)  return 0;
	Ret = SearchFish();
	if (Ret == 1)/*搜索成功*/
	{
		int OnlySearch = _ttoi(coc.getSets("OnlySearch"));
		if (OnlySearch == 1) {
			SetLog(_T("等待手动进攻完成，3分钟"), true, BLUECOLOR, false);
			Delay(330000);
			return WaitForReturnHome();
		}
		int AttackType = _ttoi(coc.getSets("AttackDeadbaseStyle"));
		switch (AttackType)
		{
		case 0:
			SetLog(_T("智能攻击"), true, RGB(0xff, 0x00, 0x00), true);
			Ret = Attack_Intel(); //下兵

			break;
		case 1:
			SetLog(_T("均分式攻击"), true, RGB(0xff, 0x00, 0x00), true);
			Ret = Attack_Equal();

			break;
		case 2:/*lua 脚本攻击*/
			SetLog(_T("lua 脚本攻击"), true, RGB(0xff, 0x00, 0x00), true);
			Ret = Attack_lua(); //下兵
			break;

		}
		LootRecord[SwitchNo].AttackCount++;
		/*等待返回*/
		Ret = WaitForReturnHome();
		return Ret;
	}
	else/*搜索失败*/
	{
		return -1;
	}

}

int CScript::script_init()
{
	CString str;
	//1.变量初始化
	SetLog("初始化...", true, BLACKCOLOR, true);
	coc.Initialize();
	townLevel = _ttoi(coc.getSets("townLevel")) + 2;
	m_base_path = GetCurrentPath();
	//这是切换信息初始化
	//a.主账号
	cocInfo[0].IsSwitch = true;
	cocInfo[0].configName = coc.GetPath();
	cocInfo[0].AppID = _ttoi(coc.getSets("GameVersion"));
	//b.子账号
	for (int i = 1; i < MAX_SWITCH_COUNT; i++)
	{
		str.Format("IsSwitch --Index %d", i);
		cocInfo[i].IsSwitch = _ttoi(coc.getSets(str));
		str.Format("ConfigPath --Index %d", i);
		cocInfo[i].configName = coc.getSets(str);
		str.Format("CocVersion --Index %d", i);
		cocInfo[i].AppID = _ttoi(coc.getSets(str));
		LootRecord[i].InitlizeDetail();
	}
	SwitchNo = 0;
	//coc 编号
	AppCocID = _ttoi(coc.getSets("GameVersion"));
	//是否下线
	IsOffLine = _ttoi(coc.getSets("OffLine"));
	//是否切换
	IsSwitch = _ttoi(coc.getSets("IsSwitchMode"));
	//是否随机延迟
	IsDelay = _ttoi(coc.getSets("IsDelay"));
	switch (townLevel)/*初始化总人口*/
	{
	case 2:
		army_capacity = 30;
		break;
	case 3:
		army_capacity = 2 * 35;
		break;
	case 4:
		army_capacity = 2 * 40;
		break;
	case 5:
		army_capacity = 3 * 45;
		break;
	case 6:
		army_capacity = 3 * 50;
		break;
	case 7:
		army_capacity = 4 * 50;
		break;
	case 8:
		army_capacity = 4 * 50;
		break;
	case 9:
		army_capacity = 4 * 55;
		break;
	case 10:
		army_capacity = 4 * 60;
		break;
	case 11:
		army_capacity = 4 * 65;
		break;
	case 12:
		army_capacity = 4 * 70;
		break;
	case 13:
		army_capacity = 4 * 75;
		break;
	default:
		army_capacity = 200;
		break;
	}

	//2.创建大漠对象
	if (false == CreateDm())
	{
		IsThreadRun = false;
		AfxMessageBox(_T("启动失败，请检查插件是否注册！"), MB_OK);
	}

	//3.检测插件版本
	if (dm.Ver() != DM_VER_5 && dm.Ver() != DM_VER_6)
	{
		IsThreadRun = false;
		AfxMessageBox(_T("启动失败，插件版本不正确，请检查插件是否注册！"), MB_OK);
		return 0;
	}

	//4.设置错误提示
	dm.SetShowErrorMsg(_ttoi(coc.getSets("SetShowErrorMsg")));
	Delay(500);

	//5.检查adb路径是否正确
	if (!PathFileExists(appPlayerInstallDir))
	{
		AfxMessageBox("模拟器路径错误，请重新设置！");
		IsThreadRun = false;
		return 0;
	}

	int ret = 0;
	//等待模拟器启动完成
	auto waitAppPlayer = [&]() {
		ret = SetBindHwnd();
		int left_time = 300;
		if (ret <= 0) /*模拟器未打开，自动打开并等待，最长300s*/
		{
			SetLog("打开模拟器，最长等待300s");
			LaunchAppPlayer(AppPlayerIndex);
			Delay(5000);
			while (_ttoi(getList2(AppPlayerIndex, 4)) == 0 &&
				IsThreadRun && left_time > 0)
			{
				Delay(1000);
				left_time--;
			}
			ret = SetBindHwnd();
			if (left_time == 0)
			{
				IsThreadRun = false;
				SetLog("启动模拟器超时!", true, REDCOLOR, false);
				return -1;
			}
		}
		return 0;
	};
	if (0 != waitAppPlayer()) {
		return -1;
	}
	
	//6.设置分辨率
	if (0 != SetAppResolution(APP_RESOLUTION_X, APP_RESOLUTION_Y)) {
		if (0 != waitAppPlayer()) {
			return -1;
		}
	}

	//7.绑定模拟器
	ret = ConnectAppPlayer();
	if (ret == -1)
	{
		IsThreadRun = false;
		return 0;
	}
	if (ret == -2)
	{
		SetLog("请检查模拟器是否打开!", true, REDCOLOR, true);
		IsThreadRun = false;
		return 0;
	}

	//8.添加字库
	AddDict();

	//9.再打开coc
	StartCoc();

	//10.到这里初始化工作已经结束，接下是主线任务
	return 1;
}

int CScript::script_main()
{
	int Ret = -1;
	//检测插件版本
	if (dm.Ver() != DM_VER_5&&dm.Ver() != DM_VER_6)
	{
		IsThreadRun = false;
		AfxMessageBox(_T("启动失败，请检查插件是否注册！"), MB_OK);
		return 0;
	}
	if (false == IsThreadRun) return 0;
	//检测主屏幕
	if (WaitForMainScreen() < 0) return -1;
	if (false == IsThreadRun) return 0;
	//缩放主屏幕
	Ret = ZoomOut();
	if (false == IsThreadRun) return 0;
	Delay(1000);
	if (false == IsThreadRun) return 0;
	//资源统计
	Statistics();
	if (false == IsThreadRun) return 0;
	//资源搜集
	CollectResource();
	if (false == IsThreadRun) return 0;
	//杯段调整
	ControlTroophs();
	if (scriptInfo == ShouldRestart) return -1;
	if (false == IsThreadRun) return 0;
	//检测主屏幕
	if (WaitForMainScreen() < 0) return -1;
	//检测士兵数量
	if (false == IsThreadRun) return 0;
	Ret = CheckArmyNum(&trainTime);
	if (false == IsThreadRun) return 0;
	//攻击
	if (Ret == 1)  Ret = Attack();
	//卡白云返回
	if (scriptInfo == ShouldRestart) return -1;
	if (false == IsThreadRun) return 0;
	//检测主屏幕
	if (WaitForMainScreen() < 0) return -1;
	//造兵
	if (trainTime == 0 && LootRecord[SwitchNo].ArmyRet <= 95)
	{
		SetLog("补兵", true, BLUECOLOR, false);
		MakeArmy();
	}
	if (false == IsThreadRun) return 0;
	//随机延迟
	DelayRandTime(15, 60);
	if (false == IsThreadRun) return 0;
	//捐兵
	DonateArmy();
	if (false == IsThreadRun) return 0;
	//升级城墙
	UpGradeWall();
	if (trainTime > 2)
	{
		if (IsOffLine) scriptInfo = ShouldWaitForArmy;
		if (IsSwitch) scriptInfo = ShouldSwitch;
	}
	return 0;
}

void CScript::SetPath(const CString& path)
{
	if (path.Find(':') == 1)/*绝对路径*/
		m_file_path = path;
	else/*相对路径*/
		m_file_path = m_base_path + path;
	if (m_file_path.Right(1) != "\\")
		m_file_path.Append("\\");
}

static unsigned EntryScript(LPVOID pParam)
{
	CScript *script_info = (CScript *)pParam;
	script_info->script_init();

	// 开始脚本循环
	do
	{
		if (false == script_info->IsThreadRun) return 0;
		//主线功能
		script_info->script_main();
		//中途停止了
		if (false == script_info->IsThreadRun) return 0;
		//掉线,重启脚本
		if (script_info->scriptInfo == ShouldRestart)
		{
			script_info->RestartScript();
			//由于掉线原因，脚本到这里必须重启，故到此结束
			continue;//进入下一轮循环
		}
		if (false == script_info->IsThreadRun) return 0;
		//等待造兵
		if (script_info->scriptInfo == ShouldWaitForArmy)
		{
			script_info->WaitForTrainArmy();
		}
		if (false == script_info->IsThreadRun) return 0;
		//切换配置
		if (script_info->scriptInfo == ShouldSwitch)
		{
			script_info->SwitchCoc();
		}
		//判断脚本是否需要停止，如果不需要，则进入下一轮循环
	} while (script_info->IsThreadRun);
	return 1;
}

CScript*  StartOneScript(CScript *script_info, int index, const char* configFile)
{
	if (script_info == nullptr)
		return nullptr;
	//1.序号
	if (index >= 0) script_info->AppPlayerIndex = index;
	//2.设置配置路径
	if (configFile) script_info->coc.SetPath(configFile);
	//加载配置
	if (configFile)
		if (script_info->coc.LoadSets(configFile) == false)
		{
			AfxMessageBox("加载配置文件失败");
			return nullptr;
		}
	//3.设置窗口句柄
	//if (appHwnd > 0) script_info->bindHwnd = appHwnd;
	//4.线程标志
	script_info->IsThreadRun = true;
	script_info->scriptInfo = 1;
	// 5.创建线程
	script_info->pThread = AfxBeginThread(EntryScript, (void*)script_info, 0, 0);
	if (script_info->pThread->m_hThread == INVALID_HANDLE_VALUE)
	{
		return nullptr;
	}

	return script_info;
}

BOOL StopOneScript(CScript  *script_info)
{
	if (script_info == NULL) return FALSE;

	// 设置标志位
	//script_info->scriptInfo = -10;
	script_info->IsThreadRun = false;
	// 等待最多3秒,如果超时,就强制结束线程.危险.(有资源泄漏)
	if (script_info->pThread == NULL) return TRUE;
	if (WAIT_OBJECT_0 != WaitForSingleObject(script_info->pThread->m_hThread, 0xfff))
	{
		// 先解绑窗口. 避免窗口崩溃
		script_info->dm.UnBindWindow();
		TerminateThread(script_info->pThread->m_hThread, 0);
		//CloseHandle(script_info->pThread->m_hThread);
	}
	//释放大漠对象
	script_info->dm = NULL;
	return TRUE;
}

BOOL SuspendOneScript(CScript* script_info)
{
	if (script_info == NULL) return FALSE;
	script_info->pThread->SuspendThread();
	script_info->IsThreadRunSuspend = true;
	return TRUE;
}

BOOL ResumOneScript(CScript* script_info)
{
	if (script_info == NULL) return FALSE;
	script_info->pThread->ResumeThread();
	script_info->IsThreadRunSuspend = false;
	return TRUE;
}

BOOL SuspendAllScript(CScript* script_info[])
{
	for (int i = 0; i < MAX_THREAD_COUNT; i++)
	{
		if (script_info == NULL) continue;;
		script_info[i]->pThread->SuspendThread();
		script_info[i]->IsThreadRunSuspend = true;
	}
	return TRUE;
}

BOOL ResumAllScript(CScript* script_info[])
{
	for (int i = 0; i < MAX_THREAD_COUNT; i++)
	{
		if (script_info == NULL) continue;
		script_info[i]->pThread->ResumeThread();
		script_info[i]->IsThreadRunSuspend = false;
	}
	return TRUE;
}

BOOL StopAllScript(CScript * all_script_info[])
{
	// 先把所有标志位置0
	int i;
	for (i = 0; i < MAX_THREAD_COUNT; ++i)
	{
		if (all_script_info[i] == NULL) continue;
		all_script_info[i]->IsThreadRun = false;
	}

	// 等待所有
	for (i = 0; i < MAX_THREAD_COUNT; ++i)
	{
		if (all_script_info[i] == NULL) continue;
		// 等待最多3秒,如果超时,就强制结束线程.危险.(有资源泄漏)
		if (WAIT_OBJECT_0 != WaitForSingleObject(all_script_info[i]->pThread->m_hThread, 3000))
		{
			// 先解绑窗口. 避免窗口崩溃
			all_script_info[i]->dm.UnBindWindow();
			TerminateThread(all_script_info[i]->pThread->m_hThread, 0);
		}
		all_script_info[i]->dm = NULL;
		//释放内存
		//消去地址
		all_script_info[i] = NULL;
	}
	return TRUE;
}


int CScript::SetBindHwnd()
{
	long nHwnd = 0;
	switch (AppPlayerType)
	{
	case  APP_PLAYER_BLUESTACKS:
		nHwnd = (long) ::FindWindow(nullptr, "BlueStacks App Player");
		break;
	case APP_PLAYER_LIGHTING:
		nHwnd = _ttoi(getList2(AppPlayerIndex, 3));
		break;
	default:
		break;
	}
	if (nHwnd > 0)
	{
		bindHwnd = nHwnd;
		return 1;
	}
	else
	{
		bindHwnd = 0;
		return 0;
	}
}

CString CScript::getList2(int x, int y)
{
	// 获取雷电多模拟器list的信息
	// x 是第x个模拟器
	// y 是模拟器的信息，index,name,_,hwnd,is_run,_,_
	CString str;
	using namespace std;
	vector<string> vstr1, vstr2;
	if (AppPlayerType == APP_PLAYER_LIGHTING)
	{
		adb.start(appPlayerInstallDir + "\\dnconsole.exe list2");
		adb.stop();
		str = adb.get_result();
		if (str.GetLength() <= 4) return "";
		_split(str.GetBuffer(), vstr1, "\n");
		str.ReleaseBuffer();
		if (vstr1.size() <= x) return "";
		if (vstr1[x].length() <= 1) return "";
		_split(vstr1[x], vstr2, ",");
		if (vstr2.size() <= y) return "";
		return CString(vstr2[y].c_str());
	}
	return "";
}
