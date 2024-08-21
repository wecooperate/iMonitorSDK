//******************************************************************************
/*++
	Description:
	
	�ļ�������

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGFileCreate)
			return;

		cxMSGFileCreate* msg = (cxMSGFileCreate*)Message;

		//
		// ������ .json ���ļ������޸ġ�ɾ��
		//

		if (FlagOn(msg->Access(), DELETE | FILE_WRITE_DATA)) {
			if (msg->IsMatchPath(L"*.json")) {
				msg->SetBlock();
			}
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

	//
	// emMSGConfigSend ͬ���¼�������SetBlock��ֹ��Ӧ�Ķ���
	//

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGFileCreate] = emMSGConfigSend;
	manager.InControl(config);

	cxMSGUserSetSessionConfig sconfig;
	sconfig.FilterFileCreateOnlyModifiable = TRUE;
	manager.InControl(sconfig);

	WaitForExit("������ .json ���ļ������޸ġ�ɾ��");

	return 0;
}
//******************************************************************************
