//******************************************************************************
/*++
	Description:

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGWFPTcpConnect)
			return;

		cxMSGWFPTcpConnect* msg = (cxMSGWFPTcpConnect*)Message;

		//
		// �ض���123.123.123.123�ĵ�ַ��127.0.0.1
		//

		if (msg->IP().IPv4.IP == 0x7B7B7B7B) {
			printf("redirect\n");
			msg->SetIPRedirect(0x0100007F, msg->Port());
		}
	}
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

	manager.InControl(cxMSGUserSetGlobalConfig());

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGWFPTcpConnect] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("�ض���123.123.123.123�ĵ�ַ��127.0.0.1");

	return 0;
}
//******************************************************************************
