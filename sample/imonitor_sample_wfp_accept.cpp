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
		// ��ֹ���ʱ���80�˿�
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

	WaitForExit("��ֹ���ʱ���80�˿�");

	return 0;
}
//******************************************************************************
