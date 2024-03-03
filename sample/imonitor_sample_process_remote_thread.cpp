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
		if (Message->GetType() != emMSGThreadCreate)
			return;

		cxMSGThreadCreate* msg = (cxMSGThreadCreate*)Message;

		if (msg->RemoteThread()) {
			//
			// ���̸ղŴ�����ʱ�򣬸�����Ҳ�ᴴ��Զ���̣߳����й���
			//
			printf("found remote thread : %S -> %S\n", msg->CurrentProcessPath(), msg->Path());
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
	config.Config[emMSGThreadCreate] = emMSGConfigPost;
	manager.InControl(config);

	WaitForExit("���Զ���߳�");

	return 0;
}
//******************************************************************************
