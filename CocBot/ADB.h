#pragma once
#ifndef _ADB_H__
#define _ADB_H__
#include <string> 
#include "pipeshell.h"
using std::string;
/*adb类*/
class ADB
{
public:
	ADB();
	~ADB();
public:
	/*adb path*/
	string m_adb_path;
	/*设备名称*/
	string m_serial_number;
private:
	CPipeShell m_pipe;
public:/*方法*/
	bool set_adb_path(string path);
	bool set_current_serial_number(string serial_num);
	//查看版本
	string version();
	//查看连接设备
	string devices();
	// 安装应用程序
	string install(string flag, string apk_name);
	// 直接卸载
	string uninstall(string flag, string package);
	// 启动 adb server
	string start_server();
	// 停止 adb server
	string kill_server();
	// 列出手机装的所有app的包名,列出系统应用的所有包名,列出除了系统应用的第三方应用包名
	string list_packages(string flag);
	// 清除应用数据与缓存
	string clear_data(string package_name);
	// 启动应用
	string run_app(string package_name, string activity_name);
	// 强制停止应用,有些时候应用卡死了，需要强制停止，则执行以下命令
	string force_stop(string package_name);
	// 查看日志
	string logcat();
	// 重启
	string reboot();
	// 查看前台 Activity
	string dumpsys_activity_activites();
	// 查看正在运行的 Services
	string dumpsys_activity_services(string package_name);
	// 调起 Service
	string start_service(string options, string activity);
	// 发送广播
	string broadcast(string options, string activity);
	//=================file manage =================

	// 复制设备里的文件到电脑
	string pull(string device_path, string pc_path);
	// 复制电脑里的文件到设备
	string push(string pc_path, string device_path);
	// 模拟按键/输入
	string input_keyevent(int keycode);
	// 滑动
	string swipe(int x1, int y1, int x2, int y2);
	// 输入文本
	string input_text(string text);
	//=====================查看设备信息===============

	// 查看设备信息
	string get_prop();
	// 电池状况
	string dumpsys_battery();
	// 屏幕分辨率
	string wm_size();
	// 屏幕密度
	string wm_density();
	// 显示屏参数
	string dumpsys_window_displays();
	// android_id
	string settings_get_secure_android_id();
	// IMEI
	string dumpsys_iphonesubinfo();
	//Android 系统版本
	string android_version();
	//ip
	string ip_address();
	//mac
	string mac_address();
	//cpu info
	string cpu_info();
	//mem info
	string mem_info();
	//more info
	string more_system_info();
	//====================修改设置================
	//分辨率
	string set_wm_size(int w, int h);
	//屏幕密度
	string set_density(int n);
	//显示区域
	string set_wm_over_scan(int x1, int y1, int x2, int y2);
	//关闭 USB 调试模式
	string disable_adb();
	//状态栏和导航栏的显示隐藏
	string set_policy_control(string key, string value);
	//===================实用功能======================
	//屏幕截图
	string screen_cap(string pc_file_name);
	//如果 adb 版本较老，无法使用 exec-out 命令，这时候建议更新 adb 版本。无法更新的话可以使用以下麻烦点的办法
	string screen_cap2(string file_name);
	//录制屏幕
	string screen_record(string file_name);
	//命令行，不需加adb
	string cmd(string str_cmd);
};
#endif


