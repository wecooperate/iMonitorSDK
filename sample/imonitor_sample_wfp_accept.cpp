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
		if (Message->GetType() != emMSGWFPTcpAccept)
			return;

		cxMSGWFPTcpAccept* msg = (cxMSGWFPTcpAccept*)Message;

		//
		// 禁止访问本地80端口
		//

		if (msg->LocalPort() == 0x5000) {
			msg->SetBlock();
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

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGWFPTcpAccept] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("禁止访问本地80端口");

	return 0;
}
//******************************************************************************
