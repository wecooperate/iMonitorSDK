//******************************************************************************
/*++
	Description:

	��ʾ��ֻ��ʾ�򵥵��������أ�
	��ֹ����url��git�ĵ�ַ���������ͨ��	HTTPChannel::ProcessRule �Լ��޸Ĳ���

	������ڳ���Ĳ�Ʒ�������ڣ�������Ϊ���������ˡ����ؼ�ء��ʼ���ء�
		�������׼�롢Э�������Э���Զ������Եȳ�����
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

		m_AgentEngine->Agent(Message, &m_HTTPManager, true);
	}

public:
	HTTPChannelManager m_HTTPManager;
	CComPtr<IMonitorAgentEngine> m_AgentEngine;
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

	callback.m_AgentEngine = manager.CreateAgentEngine();

	if (!callback.m_AgentEngine) {
		printf("create agent service failed\n");
		return 0;
	}

	manager.InControl(cxMSGUserSetGlobalConfig());

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGWFPTcpConnect] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("����������Ϊ��������ʾ: ��ֹ����url��git�ĵ�ַ\n");

	return 0;
}
//******************************************************************************
