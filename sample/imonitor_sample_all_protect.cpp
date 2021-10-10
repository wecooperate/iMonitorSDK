//******************************************************************************
/*++
	Description:
		自保护规则设置

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* msg) override
	{
	}
};
//******************************************************************************
int main()
{
	MonitorManager manager;
	MonitorCallback callback;

	HRESULT hr = manager.Start(&callback);

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 0;
	}

	manager.InControl(cxMSGUserEnableProtect());

	//
	// Path路径支持通配符
	//	* 表示任意n个字符
	//	? 表示任意一个字符
	//	> 用于字符串结尾，表示字符串结束或者是\\结尾，用于目录判断（比如protect> 匹配 protect 和 protect\\*）
	//
	{
		//
		// 添加进程、文件保护： 保护进程名是notepad.exe的进程不被结束、文件不被修改、删除
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeProcessPath | emProtectTypeFilePath;
		wcsncpy(rule.Path, L"*\\notepad.exe", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		//
		// 添加文件夹保护： 保护protect目录下面的文件不被外部修改、目录不被重命名、删除
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeFilePath;
		wcsncpy(rule.Path, L"*\\protect>", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		//
		// 添加注册表保护： 保护iMonitor键不被删除、修改，包括键值
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeRegPath;
		wcsncpy(rule.Path, L"*\\iMonitor>", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		//
		// 添加信任进程：可以操作被保护的进程、文件、注册表，但是进程本身不受保护
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeTrustProcess;
		wcsncpy(rule.Path, L"*taskkill*", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	WaitForExit("自保护开启中");

	manager.InControl(cxMSGUserRemoveAllProtectRule());
	manager.InControl(cxMSGUserDisableProtect());

	return 0;
}
//******************************************************************************
