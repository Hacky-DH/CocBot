#include "stdafx.h"
#include "lua_func.h"
#include "ImageLib.h"


int SetLog(lua_State* L)
{
	LPCTSTR log_str = luaL_checklstring(L, 1, NULL);
	int bshow = luaL_checknumber(L, 2);
	LPCTSTR color = luaL_checklstring(L, 3, NULL);
	int bsave = luaL_checknumber(L, 4);
	lua_pop(L, 4);/*弹出*/
	
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);/*取模拟器编号栈顶*/
	CString str;
	
	str = color;
	str.MakeLower();
	DWORD ncolor;
	str = script[index].dm.RGB2BGR(color);
	sscanf_s(str, "%x", &ncolor);
	script[index].SetLog(log_str, bshow, ncolor, bsave);
	
	return 0;
}

int GetColor(lua_State* L)
{

	int x, y;
	x = luaL_checknumber(L, 1);
	y = luaL_checknumber(L, 2);
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	CString str = script[index].dm.GetColor(x, y);
	lua_pop(L, 2);
	lua_pushlstring(L, str, str.GetLength());
	return 1;

}

int Tap(lua_State* L)
{
	int x, y;
	x = luaL_checknumber(L, 1);
	y = luaL_checknumber(L, 2);
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	script[index].dm.MoveTo(x, y);
	script[index].Dealy(20);
	script[index].dm.LeftClick();
	lua_pop(L, 2);
	return 0;
}

int FindColor(lua_State* L)
{
	LPCTSTR color = luaL_checklstring(L, 1, NULL);
	double sim = luaL_checknumber(L, 2);
	VARIANT vx, vy;
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	script[index].dm.FindColor(0, 0, 850, 667, color, sim, 0, &vx, &vy);
	lua_pop(L, 2);
	lua_pushnumber(L, vx.lVal);
	lua_pushnumber(L, vy.lVal);
	return 2;
}

int FindColorEx(lua_State* L)
{
	long x1, y1, x2, y2;
	x1 = luaL_checknumber(L, 1);
	y1 = luaL_checknumber(L, 2);
	x2 = luaL_checknumber(L, 3);
	y2 = luaL_checknumber(L, 4);
	LPCTSTR color = luaL_checklstring(L, 5, NULL);
	double sim = luaL_checknumber(L, 6);
	VARIANT vx, vy;
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	script[index].dm.FindColor(x1, y1, x2, y2, color, sim, 0, &vx, &vy);
	lua_pop(L, 6);
	lua_pushnumber(L, vx.lVal);
	lua_pushnumber(L, vy.lVal);
	return 2;
}

int FindMultiColor(lua_State* L)
{
	LPCTSTR first_color = luaL_checklstring(L, 1, NULL);
	LPCTSTR offset_color = luaL_checklstring(L, 2, NULL);
	double sim = luaL_checknumber(L, 3);
	VARIANT vx, vy;
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	script[index].dm.FindMultiColor(0, 0, 850, 667, first_color, offset_color, sim, 0, &vx, &vy);
	lua_pop(L, 3);
	lua_pushnumber(L, vx.lVal);
	lua_pushnumber(L, vy.lVal);
	return 2;
}

int FindMultiColorEx(lua_State* L)
{
	long x1, y1, x2, y2;
	x1 = luaL_checknumber(L, 1);
	y1 = luaL_checknumber(L, 2);
	x2 = luaL_checknumber(L, 3);
	y2 = luaL_checknumber(L, 4);
	LPCTSTR first_color = luaL_checklstring(L, 5, NULL);
	LPCTSTR offset_color = luaL_checklstring(L, 6, NULL);
	double sim = luaL_checknumber(L, 7);
	VARIANT vx, vy;
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	script[index].dm.FindMultiColor(x1, y1, x2, y2, first_color, offset_color, sim, 0, &vx, &vy);
	lua_pop(L, 7);
	lua_pushnumber(L, vx.lVal);
	lua_pushnumber(L, vy.lVal);
	return 2;
}

int FindPic(lua_State* L)
{
	LPCTSTR pic_name = luaL_checklstring(L, 1, NULL);
	LPCTSTR delta_color = luaL_checklstring(L, 2, NULL);
	double sim = luaL_checknumber(L, 3);
	VARIANT vx, vy;
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	script[index].dm.FindPic(0, 0, 850, 677, pic_name, delta_color, sim, 0, &vx, &vy);
	lua_pop(L, 3);
	lua_pushnumber(L, vx.lVal);
	lua_pushnumber(L, vy.lVal);
	return 2;
}

int FindPicEx(lua_State* L)
{
	long x1, y1, x2, y2;
	x1 = luaL_checknumber(L, 1);
	y1 = luaL_checknumber(L, 2);
	x2 = luaL_checknumber(L, 3);
	y2 = luaL_checknumber(L, 4);
	LPCTSTR pic_name = luaL_checklstring(L, 5, NULL);
	LPCTSTR delta_color = luaL_checklstring(L, 6, NULL);
	double sim = luaL_checknumber(L, 7);
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	void* p = (void*)script[index].dm.GetScreenData(x1, y1, x2, y2);
	int retx, rety;
	int ret=ImageLoc(x2-x1,y2-y1,p, pic_name, sim, &retx, &rety);
	lua_pop(L, 7);
	switch (ret)
	{
	case 1:
		script[index].SetLog("ok");
		break;
	case 0:
		script[index].SetLog("not ok");
		break;
	case -1:
		script[index].SetLog("src mat false");
		break;
	case -2:
		script[index].SetLog("temp mat false");
		break;
	default:
		break;
	}
	if (ret == 1)
	{
		retx += x1;
		rety += y1;
	}
	lua_pushnumber(L, retx);
	lua_pushnumber(L, rety);
	return 2;
}

int SetPath(lua_State* L)
{
	LPCTSTR path = luaL_checklstring(L, 1, NULL);
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	script[index].dm.SetPath(path);
	lua_pop(L, 1);
	return 0;
}

int Dealy(lua_State* L)
{
	int seconds = luaL_checknumber(L, 1);
	if (seconds < 0)seconds = 1;
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	script[index].Dealy(seconds);
	lua_pop(L, 1);
	return 0;
}

int SelectSolider(lua_State* L)
{
	int type = luaL_checknumber(L, 1);
	type = type < 0 || type>20 ? 1 : type;
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	int lua_ret=script[index].SelectSolider(type);
	lua_pop(L, 1);
	lua_pushnumber(L, lua_ret);
	return 1;
}

int GetAttackPos(lua_State* L)
{
	long x1, y1, x2, y2;
	x1 = luaL_checknumber(L, 1);
	y1 = luaL_checknumber(L, 2);
	x2 = luaL_checknumber(L, 3);
	y2 = luaL_checknumber(L, 4);
	CString str;
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	str=script[index].dm.FindColorBlockEx(x1, y1, x2, y2, "a7b052-050f0f|9cb24a-050f0f|bad058-050f0f|adbc52-050f0f", 1, 30, 6, 6);
	lua_pop(L,4);
	using namespace std;
	vector<string> vstr, vstrx, vstry;
	_split(str.GetBuffer(), vstr, "|");
	if (vstr.size() == 2)
	{
		_split(vstr[0], vstrx, ",");
		_split(vstr[1], vstry, ",");
		lua_newtable(L);/*创建一个表x*/
		lua_pushnumber(L, -1);
		lua_rawseti(L, -2, 0);
		for (int i=0;i<vstrx.size();i++)
		{
			lua_pushinteger(L, atoi(vstrx[i].c_str()));
			lua_rawseti(L, -2, i + 1);
		}
		lua_newtable(L);/*创建一个表y*/
		lua_pushnumber(L, -1);
		lua_rawseti(L, -2, 0);
		for (int i = 0; i < vstry.size(); i++)
		{
			lua_pushinteger(L, atoi(vstry[i].c_str()));
			lua_rawseti(L, -2, i + 1);
		}
	}
	//lua_pushlstring(L, str, str.GetLength());
	return 2;/*返回两个表*/
	
}

int GetAttackPosEx(lua_State* L)
{
	long x1, y1, x2, y2;
	x1 = luaL_checknumber(L, 1);
	y1 = luaL_checknumber(L, 2);
	x2 = luaL_checknumber(L, 3);
	y2 = luaL_checknumber(L, 4);
	CString str;
	DWORD t1 = GetTickCount();
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	str = script[index].dm.FindColorBlockEx(x1, y1, x2, y2, "a7b052-050f0f|9cb24a-050f0f|bad058-050f0f|adbc52-050f0f", 1, 30, 6, 6);
	CString str2;
	str2.Format("FindColorBlockEx(%d, %d, %d, %d} time:%dms", x1, y1, x2, y2, GetTickCount() - t1);
	script[index].SetLog(str2);
	lua_pop(L, 4);/*弹出无用的数据*/
	using namespace std;
	vector<string> vstr, vstrx, vstry;
	_split(str.GetBuffer(), vstr, "|");
	str.ReleaseBuffer();
	int i;
	if (vstr.size() == 2)
	{
		_split(vstr[0], vstrx, ",");
		_split(vstr[1], vstry, ",");
		int nPos = min(vstrx.size(), vstry.size());
		if (nPos>0)
		{
			int nx[MAX_ARMY_COUNT], ny[MAX_ARMY_COUNT];
			
			long* allx = new long[nPos];
			long* ally = new long[nPos];
			for (i = 0; i < nPos; i++)
			{
				allx[i] = atoi(vstrx[i].c_str());
				ally[i] = atoi(vstry[i].c_str());
			}
			int best_index = 0;
			for (i = 0; i < MAX_ARMY_COUNT; i++)
			{
				best_index = Array::FindNearestPos<long>(allx, ally, nPos, ATTACK_CIRCLE_X[i], ATTACK_CIRCLE_Y[i]);
				nx[i] = allx[best_index];
				ny[i] = ally[best_index];
			}
			delete[]allx;
			delete[]ally;
			lua_newtable(L);/*创建一个表x*/
			lua_pushnumber(L, -1);
			lua_rawseti(L, -2, 0);
			for (i = 0; i < MAX_ARMY_COUNT; i++)
			{
				lua_pushinteger(L, nx[i]);
				lua_rawseti(L, -2, i + 1);
			}
			lua_newtable(L);/*创建一个表y*/
			lua_pushnumber(L, -1);
			lua_rawseti(L, -2, 0);
			for (i = 0; i < MAX_ARMY_COUNT; i++)
			{
				lua_pushinteger(L, ny[i]);
				lua_rawseti(L, -2, i + 1);
			}
		}
	
	}
	return 2;/*返回两个表*/
}

int SelectSpell(lua_State* L)
{
	int type = luaL_checknumber(L, 1);
	type = type < 0 || type>10 ? 1 : type;
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	int lua_ret = script[index].SelectSpell(type);
	lua_pop(L, 1);
	lua_pushnumber(L, lua_ret);
	return 1;
}

int SelectHero(lua_State* L)
{
	int type = luaL_checknumber(L, 1);
	type = type < 0 || type>3 ? 1 : type;
	lua_getglobal(L, "g_app_player_index");
	int index = luaL_checknumber(L, -1);
	int lua_ret = script[index].SelectHero(type);
	lua_pop(L, 1);
	lua_pushnumber(L, lua_ret);
	return 1;
}

