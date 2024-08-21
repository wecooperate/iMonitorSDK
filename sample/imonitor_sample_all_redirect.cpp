//******************************************************************************
/*++
	Description:

	文件重定向示例：
		针对cmd.exe，将目录 C:\ProgramData 重定向到 C:\Data 目录
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
	//
	// 注意：需要先创建重定向的目录，否则会导致找不到路径
	//
	CreateDirectory(L"C:\\Data", NULL);

	nlohmann::json rule;
	rule["processes"].push_back("*\\cmd.exe");

	nlohmann::json pair;
	pair["source"] = "C:\\ProgramData";
	pair["target"] = "C:\\Data";

	rule["files"].push_back(pair);

	nlohmann::json rules;
	rules.push_back(rule);

	return UTF8StringToDriverString(rules.dump());
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
	manager.SetRules(emUserSetRedirectorRules, rules.c_str());

	WaitForExit("针对cmd.exe，将目录 C:\\ProgramData 重定向到 C:\\Data 目录\n"
				"\t注意：此功能是设置，设置完成要恢复需要移除规则！\n"
				"\t按任意键移除规则并退出。");

	manager.InControl(cxMSGUserRemoveRedirectorRules());

	return 0;
}
//******************************************************************************
