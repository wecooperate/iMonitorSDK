//******************************************************************************
/*++
	Description:

	��̬���������ʾ����
		��ֹ dbgmsgcfg.dll ��ģ�鱻����

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGImageLoad)
			return;

		cxMSGImageLoad* msg = (cxMSGImageLoad*)Message;

		//
		// ��ֹ dbgmsgcfg.dll ��ģ�鱻����
		//

		if (msg->IsMatchPath(L"*\\dbgmsgcfg.dll"))
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

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGImageLoad] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("��ֹ dbgmsgcfg.dll ��ģ�鱻����");

	return 0;
}
//******************************************************************************
