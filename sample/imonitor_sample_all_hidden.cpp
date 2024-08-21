//******************************************************************************
/*++
	Description:

	文件隐藏示例：
		隐藏后缀名是.docx和文件夹是"隐藏文件夹"的文件

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
	nlohmann::json rule;
	rule["files"].push_back("*.docx");
	rule["files"].push_back(u8"*\\隐藏文件夹>");

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
	manager.SetRules(emUserSetHiddenRules, rules.c_str());

	WaitForExit("隐藏后缀名是.docx和文件夹是\"隐藏文件夹\"的文件。\n"
				"\t注意：此功能是设置，设置完成要恢复需要移除规则！\n"
				"\t按任意键移除规则并退出。");

	manager.InControl(cxMSGUserRemoveHiddenRules());

	return 0;
}
//******************************************************************************
