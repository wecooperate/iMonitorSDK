//******************************************************************************
/*++
	Description:

	�ļ�����ʾ����
		���غ�׺����.docx���ļ�����"�����ļ���"���ļ�

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
	rule["files"].push_back(u8"*\\�����ļ���>");

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

	WaitForExit("���غ�׺����.docx���ļ�����\"�����ļ���\"���ļ���\n"
				"\tע�⣺�˹��������ã��������Ҫ�ָ���Ҫ�Ƴ�����\n"
				"\t��������Ƴ������˳���");

	manager.InControl(cxMSGUserRemoveHiddenRules());

	return 0;
}
//******************************************************************************
