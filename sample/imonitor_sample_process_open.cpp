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
		if (Message->GetType() != emMSGProcessOpen)
			return;

		cxMSGProcessOpen* msg = (cxMSGProcessOpen*)Message;

		//
		// ��ֹ����notepad.exe
		//	 �����Ҫ�Ա�����ο��Ա������ܣ���ֹ����������������ʽ�������̣�Զ��ע�롢�����ڴ�ȣ�
		//

		if (msg->IsMatchPath(L"*\\notepad.exe"))
			msg->SetGrantedAccess(msg->DesiredAccess() & ~PROCESS_TERMINATE);
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
	config.Config[emMSGProcessOpen] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("��ֹ����notepad.exe");

	return 0;
}
//******************************************************************************
