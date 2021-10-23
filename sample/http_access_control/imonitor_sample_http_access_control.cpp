//******************************************************************************
/*++
	Description:

--*/
//******************************************************************************
#include "imonitor_sample.h"
#include "http_channel.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGWFPTcpConnect)
			return;

		if (Message->GetCurrentProcessId() == 12892)
			return;

		m_AgentService->Agent(Message, &m_HTTPManager, true);
	}

public:
	HTTPChannelManager m_HTTPManager;
	CComPtr<IAgentService> m_AgentService;
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

	callback.m_AgentService = manager.CreateAgentService();

	if (!callback.m_AgentService) {
		printf("create agent service failed\n");
		return 0;
	}

	manager.InControl(cxMSGUserSetGlobalConfig());

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGWFPTcpConnect] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("启动上网行为管理功能演示: 禁止访问url带git的地址\n");

	return 0;
}
//******************************************************************************
