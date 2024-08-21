//******************************************************************************
/*++
	Description:

	规则引擎使用示例

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback
	: public IMonitorCallback
	, public IMonitorMatchCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		m_RuleEngine->Match(Message, this);
	}

	emMatchStatus OnMatch(IMonitorMessage* Message, IMonitorRule* Rule) override
	{
		if (Rule->GetAction() & emMSGActionBlock) {
			printf("match rule!\n");
			Message->SetBlock();
			return emMatchStatusBreak;
		}

		return emMatchStatusContinue;
	}

public:
	CComPtr<IMonitorRuleEngine> m_RuleEngine;
};
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

	WCHAR rule_path[MAX_PATH] = {};
	GetModuleFileName(NULL, rule_path, MAX_PATH);
	PathRemoveFileSpec(rule_path);
	PathAppend(rule_path, L"iMonitor.rule");

	callback.m_RuleEngine = manager.CreateRuleEngine(rule_path);

	if (!callback.m_RuleEngine) {
		printf("load rule failed\n");
		return 0;
	}

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGProcessCreate] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("匹配规则：iMonitor.rule");

	return 0;
}
//******************************************************************************
