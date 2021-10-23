//******************************************************************************
/*++
	Description:
		本示例只显示简单的上网拦截：
		禁止访问url带git的地址，规则可以通过	HTTPChannel::ProcessRule 自己修改测试

		本框架在成熟的产品里曾用于：上网行为管理、广告过滤、下载监控、邮件监控、
			网络代理、准入、协议分析、协议自动化测试等场景。
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
