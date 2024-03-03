//******************************************************************************
/*++
	Description:

	轻量级文件沙箱使用示例：
		notepad.exe 运行在沙箱，修改的文件会自动重定向到沙箱里面

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
std::string InitRules(void)
{
	return R"(
	[
        {
            "sandbox_name" : "test",
            "sandbox_root" : "C:\\sandbox",
			"processes": ["*\\notepad.exe"],
			"include_child_processes": true,
			"include_exist_processes": true
        }
    ]
)";
}
//******************************************************************************
int main()
{
	MonitorManager manager;
	MonitorCallback callback;

	HRESULT hr = manager.Start(&callback);

	CheckSignError(hr);

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 0;
	}

	std::string rules = InitRules();
	hr = manager.SetRules(emUserSetSandboxRules, rules.c_str());

	if (hr != S_OK) {
		printf("set rules failed = %08X\n", hr);
		return 0;
	}

	WaitForExit("将notepad.exe加入到沙箱执行。\n"
				"\t注意：此功能是设置，设置完成要恢复需要移除规则！\n"
				"\t按任意键移除规则并退出。");

	manager.InControl(cxMSGUserRemoveSandboxRules());

	return 0;
}
//******************************************************************************
