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
		cxMSGWFPTcpConnect* msg = (cxMSGWFPTcpConnect*)Message;

		//
		// ��ֹ����443�˿�
		//

		if (msg->Port() == 0xBB01) {
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

	manager.InControl(cxMSGUserSetGlobalConfig());

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGWFPTcpConnect] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("��ֹ����443�˿�");

	return 0;
}
//******************************************************************************
