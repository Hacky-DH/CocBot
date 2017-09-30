#include "stdafx.h"
#include "ADB.h"


ADB::ADB()
{
}


ADB::~ADB()
{
}


bool ADB::set_adb_path(string path)
{
	m_adb_path = path;
	return true;
}


bool ADB::set_current_serial_number(string serial_num)
{
	m_serial_number = serial_num;
	return true;
}

string ADB::version()
{
	m_pipe.start(m_adb_path + " version");
	m_pipe.stop();
	return m_pipe.get_result();
}


string ADB::devices()
{

	m_pipe.start(m_adb_path + " devices");
	m_pipe.stop();
	return m_pipe.get_result();
}


// 安装应用程序
string ADB::install(string flag, string apk_name)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number + " install " + flag + " " + apk_name);
	else
		m_pipe.start(m_adb_path + " install " + flag + " " + apk_name);
	m_pipe.stop();

	return m_pipe.get_result();
}


// 直接卸载
string ADB::uninstall(string flag, string package)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number + " uninstall " + flag + " " + package);
	else
		m_pipe.start(m_adb_path + " uninstall " + flag + " " + package);
	m_pipe.stop();

	return m_pipe.get_result();
}


// 启动 adb server
string ADB::start_server()
{
	m_pipe.start(m_adb_path + " start-server");
	m_pipe.stop();

	return m_pipe.get_result();
}


// 启动 adb server
string ADB::kill_server()
{
	m_pipe.start(m_adb_path + " kill-server");
	m_pipe.stop();

	return m_pipe.get_result();
}


// 列出手机装的所有app的包名,列出系统应用的所有包名,列出除了系统应用的第三方应用包名
string ADB::list_packages(string flag)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number + " shell pm list packages " + flag);
	else
		m_pipe.start(m_adb_path + " shell pm list packages " + flag);

	m_pipe.stop();

	return m_pipe.get_result();
}


// 清除应用数据与缓存
string ADB::clear_data(string package_name)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number + " shell pm clear " + package_name);
	else
		m_pipe.start(m_adb_path + " shell pm clear " + package_name);
	m_pipe.stop();

	return m_pipe.get_result();
}


// 启动应用
string ADB::run_app(string package_name, string activity_name)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number + " shell am start -n " + package_name + "/" + activity_name);
	else
		m_pipe.start(m_adb_path + " shell am start -n " + package_name + "/" + activity_name);
	m_pipe.stop();

	return m_pipe.get_result();
}

// 强制停止应用,有些时候应用卡死了，需要强制停止，则执行以下命令
string ADB::force_stop(string package_name)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number + " shell am force-stop " + package_name);
	else
		m_pipe.start(m_adb_path + " shell am force-stop " + package_name);
	m_pipe.stop();

	return m_pipe.get_result();
}


// 查看日志
string ADB::logcat()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number + " logcat");
	else
		m_pipe.start(m_adb_path + " logcat");
	m_pipe.stop();

	return m_pipe.get_result();
}


// 重启
string ADB::reboot()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number + " reboot");
	else
		m_pipe.start(m_adb_path + " reboot");
	m_pipe.stop();

	return m_pipe.get_result();
}


// 查看前台 Activity
string ADB::dumpsys_activity_activites()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number + " shell dumpsys activity activities");
	else
		m_pipe.start(m_adb_path + " shell dumpsys activity activities");
	m_pipe.stop();

	return m_pipe.get_result();
}


// 查看正在运行的 Services
string ADB::dumpsys_activity_services(string package_name)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number + " shell dumpsys activity services " + package_name);
	else
		m_pipe.start(m_adb_path + " shell dumpsys activity services " + package_name);
	m_pipe.stop();

	return m_pipe.get_result();
}


// 调起 Service
string ADB::start_service(string options, string activity)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell am startservice -n " + options + "/" + activity);
	else
		m_pipe.start(m_adb_path +
			" shell am startservice -n " + options + "/" + activity);
	m_pipe.stop();

	return m_pipe.get_result();
}


string ADB::broadcast(string options, string activity)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell am broadcast -a " + options + "/" + activity);
	else
		m_pipe.start(m_adb_path +
			" shell am broadcast -a " + options + "/" + activity);
	m_pipe.stop();

	return m_pipe.get_result();
}


// 复制设备里的文件到电脑
string ADB::pull(string device_path, string pc_path)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" pull " + device_path + " " + pc_path);
	else
		m_pipe.start(m_adb_path +
			" pull " + device_path + " " + pc_path);
	m_pipe.stop();

	return m_pipe.get_result();
}


// 复制电脑里的文件到设备
string ADB::push(string pc_path, string device_path)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" push " + pc_path + " " + device_path);
	else
		m_pipe.start(m_adb_path +
			" push " + pc_path + " " + device_path);
	m_pipe.stop();

	return m_pipe.get_result();
}


// 模拟按键/输入
string ADB::input_keyevent(int keycode)
{
	char key_str[10] = { 0 };
	sprintf_s(key_str, 10, "%d", keycode);
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell input keyevent " + key_str);
	else
		m_pipe.start(m_adb_path +
			" shell input keyevent " + key_str);
	m_pipe.stop();

	return m_pipe.get_result();
}


// 滑动
string ADB::swipe(int x1, int y1, int x2, int y2)
{
	char key_str[40] = { 0 };
	sprintf_s(key_str, 40, "%d %d %d %d", x1, y1, x2, y2);
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell input swipe " + key_str);
	else
		m_pipe.start(m_adb_path +
			" shell input swipe " + key_str);
	m_pipe.stop();
	return m_pipe.get_result();

}


// 输入文本
string ADB::input_text(string text)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell input text " + text);
	else
		m_pipe.start(m_adb_path +
			" shell input text " + text);
	m_pipe.stop();
	return m_pipe.get_result();

}


// 查看设备信息
string ADB::get_prop()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell getprop ro.product.model ");
	else
		m_pipe.start(m_adb_path +
			" shell getprop ro.product.model ");
	m_pipe.stop();
	return m_pipe.get_result();
}


// 电池状况
string ADB::dumpsys_battery()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell dumpsys battery ");
	else
		m_pipe.start(m_adb_path +
			" shell dumpsys battery ");
	m_pipe.stop();
	return m_pipe.get_result();
}


// 屏幕分辨率
string ADB::wm_size()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell wm size");
	else
		m_pipe.start(m_adb_path +
			" shell wm size");
	m_pipe.stop();
	return m_pipe.get_result();
}


// 屏幕密度
string ADB::wm_density()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell wm density");
	else
		m_pipe.start(m_adb_path +
			" shell wm density");
	m_pipe.stop();
	return m_pipe.get_result();
}


// // 显示屏参数
string ADB::dumpsys_window_displays()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell dumpsys window displays");
	else
		m_pipe.start(m_adb_path +
			" shell dumpsys window displays");
	m_pipe.stop();
	return m_pipe.get_result();
}
string ADB::settings_get_secure_android_id()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell settings get secure android_id");
	else
		m_pipe.start(m_adb_path +
			" shell settings get secure android_id");
	m_pipe.stop();
	return m_pipe.get_result();
}


string ADB::dumpsys_iphonesubinfo()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell dumpsys iphonesubinfo");
	else
		m_pipe.start(m_adb_path +
			" shell dumpsys iphonesubinfo");
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::android_version()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell getprop ro.build.version.release");
	else
		m_pipe.start(m_adb_path +
			" shell getprop ro.build.version.release");
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::ip_address()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell ifconfig | grep Mask");
	else
		m_pipe.start(m_adb_path +
			" shell ifconfig | grep Mask");
	m_pipe.stop();
	return m_pipe.get_result();
}
string ADB::mac_address()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell cat /sys/class/net/wlan0/address");
	else
		m_pipe.start(m_adb_path +
			" shell cat /sys/class/net/wlan0/address");
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::cpu_info()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell cat /proc/cpuinfo");
	else
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell cat /proc/cpuinfo");
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::mem_info()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell cat /proc/meminfo");
	else
		m_pipe.start(m_adb_path +
			" shell cat /proc/meminfo");
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::more_system_info()
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell cat /system/build.prop");
	else
		m_pipe.start(m_adb_path +
			" shell cat /system/build.prop");
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::set_wm_size(int w, int h)
{
	char buff[20] = { 0 };
	sprintf_s(buff, 20, "%dx%d", w, h);
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell wm size " + buff);
	else
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell wm size " + buff);
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::set_density(int n)
{
	char buff[20] = { 0 };
	sprintf_s(buff, 20, "%d", n);
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell wm density " + buff);
	else
		m_pipe.start(m_adb_path +
			" shell wm density " + buff);
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::set_wm_over_scan(int x1, int y1, int x2, int y2)
{
	char buff[40] = { 0 };
	sprintf_s(buff, 40, "%d %d %d %d", x1, y1, x2, y2);
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell wm overscan " + buff);
	else
		m_pipe.start(m_adb_path +
			" shell wm overscan " + buff);
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::disable_adb()
{

	m_pipe.start(m_adb_path + " -s " + m_serial_number +
		" shell settings put global adb_enabled 0");
	m_pipe.stop();
	return m_pipe.get_result();
}


string ADB::set_policy_control(string key, string value)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell settings put global policy_control " + key + "=" + value);
	else
		m_pipe.start(m_adb_path +
			" shell settings put global policy_control " + key + "=" + value);
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::screen_cap(string file_name)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" exec-out screencap -p > " + file_name);
	else
		m_pipe.start(m_adb_path +
			" exec-out screencap -p > " + file_name);
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::screen_cap2(string file_name)
{
	if (m_serial_number.length() != 0)
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell screencap -p " + file_name);
	else
		m_pipe.start(m_adb_path +
			" shell screencap -p " + file_name);
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::screen_record(string file_name)
{
	if (m_serial_number.length() == 0)
		m_pipe.start(m_adb_path +
			" shell shell screenrecord " + file_name);
	else
		m_pipe.start(m_adb_path + " -s " + m_serial_number +
			" shell shell screenrecord " + file_name);
	m_pipe.stop();
	return m_pipe.get_result();
}

string ADB::cmd(string str_cmd)
{
	if (m_adb_path.length() == 0)
		m_pipe.start(str_cmd);
	else
		m_pipe.start(m_adb_path + " " + str_cmd);
	m_pipe.stop();
	return m_pipe.get_result();
}