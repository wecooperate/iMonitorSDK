//******************************************************************************
/*++
	Description:

	�ļ��ض���ʾ����
		���cmd.exe����Ŀ¼ C:\ProgramData �ض��� C:\Data Ŀ¼
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
	// ע�⣺��Ҫ�ȴ����ض����Ŀ¼������ᵼ���Ҳ���·��
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

	WaitForExit("���cmd.exe����Ŀ¼ C:\\ProgramData �ض��� C:\\Data Ŀ¼\n"
				"\tע�⣺�˹��������ã��������Ҫ�ָ���Ҫ�Ƴ�����\n"
				"\t��������Ƴ������˳���");

	manager.InControl(cxMSGUserRemoveRedirectorRules());

	return 0;
}
//******************************************************************************
