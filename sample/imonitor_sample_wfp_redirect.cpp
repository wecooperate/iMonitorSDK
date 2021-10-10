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
		// 重定向123.123.123.123的地址到127.0.0.1
		//

		if (msg->IP() == 0x7B7B7B7B) {
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

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 0;
	}

	manager.InControl(cxMSGUserSetGlobalConfig());

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGWFPTcpConnect] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("重定向123.123.123.123的地址到127.0.0.1");

	return 0;
}
//******************************************************************************
