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
		if (Message->GetType() != emMSGRegCreateKey)
			return;

		cxMSGRegCreateKey* msg = (cxMSGRegCreateKey*)Message;

		//
		// ��ֹ�򿪡������� protect ��ע�����
		//

		if (msg->IsMatchPath(L"*protect*"))
			msg->SetBlock();
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
	config.Config[emMSGRegCreateKey] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("��ֹ�򿪡������� protect ��ע�����");

	return 0;
}
//******************************************************************************
