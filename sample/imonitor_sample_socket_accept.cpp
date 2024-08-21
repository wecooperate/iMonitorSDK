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
		// ��ֹ���ʱ���80�˿�
		//	accept��ʧ�ܣ�һЩ���û�д���ʧ�ܵĳ���������쳣�� ����ʹ��WFP�Ľӿ�
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

	manager.InControl(cxMSGUserSetGlobalConfig());

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGSocketAccept] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("��ֹ���ʱ���80�˿�");

	return 0;
}
//******************************************************************************
