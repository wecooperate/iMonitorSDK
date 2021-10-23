//******************************************************************************
/*++
	Description:

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback
	: public IMonitorCallback
	, public IRuleCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		m_RuleService->Match(Message, this);
	}

	emMatchStatus OnMatch(IMonitorMessage* Message, const char* GroupName, const char* RuleName, ULONG Action, const char* ActionParam) override
	{
		if (Action & emMSGActionBlock) {
			Message->SetBlock();
			printf("match block rule %s.%s\n", GroupName, RuleName);
			return emMatchStatusBreak;
		}

		return emMatchStatusContinue;
	}

public:
	CComPtr<IRuleService> m_RuleService;
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

	WCHAR rule_path[MAX_PATH] = {};
	GetModuleFileName(NULL, rule_path, MAX_PATH);
	PathRemoveFileSpec(rule_path);
	PathAppend(rule_path, L"iMonitor.rule");

	callback.m_RuleService = manager.CreateRuleService(rule_path);

	if (!callback.m_RuleService) {
		printf("load rule failed\n");
		return 0;
	}

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGProcessCreate] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("∆•≈‰πÊ‘Ú£∫iMonitor.rule");

	return 0;
}
//******************************************************************************
