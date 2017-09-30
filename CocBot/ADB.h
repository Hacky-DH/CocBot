#pragma once
#ifndef _ADB_H__
#define _ADB_H__
#include <string> 
#include "pipeshell.h"
using std::string;
/*adb��*/
class ADB
{
public:
	ADB();
	~ADB();
public:
	/*adb path*/
	string m_adb_path;
	/*�豸����*/
	string m_serial_number;
private:
	CPipeShell m_pipe;
public:/*����*/
	bool set_adb_path(string path);
	bool set_current_serial_number(string serial_num);
	//�鿴�汾
	string version();
	//�鿴�����豸
	string devices();
	// ��װӦ�ó���
	string install(string flag, string apk_name);
	// ֱ��ж��
	string uninstall(string flag, string package);
	// ���� adb server
	string start_server();
	// ֹͣ adb server
	string kill_server();
	// �г��ֻ�װ������app�İ���,�г�ϵͳӦ�õ����а���,�г�����ϵͳӦ�õĵ�����Ӧ�ð���
	string list_packages(string flag);
	// ���Ӧ�������뻺��
	string clear_data(string package_name);
	// ����Ӧ��
	string run_app(string package_name, string activity_name);
	// ǿ��ֹͣӦ��,��Щʱ��Ӧ�ÿ����ˣ���Ҫǿ��ֹͣ����ִ����������
	string force_stop(string package_name);
	// �鿴��־
	string logcat();
	// ����
	string reboot();
	// �鿴ǰ̨ Activity
	string dumpsys_activity_activites();
	// �鿴�������е� Services
	string dumpsys_activity_services(string package_name);
	// ���� Service
	string start_service(string options, string activity);
	// ���͹㲥
	string broadcast(string options, string activity);
	//=================file manage =================

	// �����豸����ļ�������
	string pull(string device_path, string pc_path);
	// ���Ƶ�������ļ����豸
	string push(string pc_path, string device_path);
	// ģ�ⰴ��/����
	string input_keyevent(int keycode);
	// ����
	string swipe(int x1, int y1, int x2, int y2);
	// �����ı�
	string input_text(string text);
	//=====================�鿴�豸��Ϣ===============

	// �鿴�豸��Ϣ
	string get_prop();
	// ���״��
	string dumpsys_battery();
	// ��Ļ�ֱ���
	string wm_size();
	// ��Ļ�ܶ�
	string wm_density();
	// ��ʾ������
	string dumpsys_window_displays();
	// android_id
	string settings_get_secure_android_id();
	// IMEI
	string dumpsys_iphonesubinfo();
	//Android ϵͳ�汾
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
	//====================�޸�����================
	//�ֱ���
	string set_wm_size(int w, int h);
	//��Ļ�ܶ�
	string set_density(int n);
	//��ʾ����
	string set_wm_over_scan(int x1, int y1, int x2, int y2);
	//�ر� USB ����ģʽ
	string disable_adb();
	//״̬���͵���������ʾ����
	string set_policy_control(string key, string value);
	//===================ʵ�ù���======================
	//��Ļ��ͼ
	string screen_cap(string pc_file_name);
	//��� adb �汾���ϣ��޷�ʹ�� exec-out �����ʱ������� adb �汾���޷����µĻ�����ʹ�������鷳��İ취
	string screen_cap2(string file_name);
	//¼����Ļ
	string screen_record(string file_name);
	//�����У������adb
	string cmd(string str_cmd);
};
#endif


