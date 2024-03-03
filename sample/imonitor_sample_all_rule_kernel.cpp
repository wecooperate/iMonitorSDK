//******************************************************************************
/*++
	Description:

	内核规则引擎（规则直接设置在驱动生效）使用示例：
		一些太频繁的事件，如果抛到应用层执行规则引擎，效率会比较低，这种情况就可以使用内核级别的规则引擎

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
{
    "name" : "default",
    "description" : "default rule group",
    "rules" : [
        {
            "name" : "block notepad start",
            "action" : 1,
            "event" : "ProcessCreate",
            "matcher" : {
                "or" : [
                    {"match" : ["Path", "*\\notepad.exe"]},
                    {"match" : ["Path", "*\\notepad++.exe"]}
                ]
            }
        }
    ]
}
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
	manager.SetRules(emUserSetMSGRules, rules.c_str());

	WaitForExit("设置内核规则：禁止notepad的进程启动。\n"
				"\t注意：此功能是设置，设置完成要恢复需要移除规则！\n"
				"\t按任意键移除规则并退出。");

	manager.InControl(cxMSGUserRemoveMSGRules());

	return 0;
}
//******************************************************************************
