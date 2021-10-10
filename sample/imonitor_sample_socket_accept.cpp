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
		if (Message->GetType() != emMSGSocketAccept)
			return;

		cxMSGSocketAccept* msg = (cxMSGSocketAccept*)Message;

		//
		// 禁止访问本地80端口
		//	accept会失败，一些软件没有处理失败的场景会出现异常， 建议使用WFP的接口
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

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 0;
	}

	manager.InControl(cxMSGUserSetGlobalConfig());

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGSocketAccept] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("禁止访问本地80端口");

	return 0;
}
//******************************************************************************
