//******************************************************************************
/*++
	Description:
	
	����ļ�д������

--*/
//******************************************************************************
#include "imonitor_sample.h"
#include <string>
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGFilePostWrite)
			return;

		cxMSGFilePostWrite* msg = (cxMSGFilePostWrite*)Message;

		if (!msg->IsMatchPath(L"*.json"))
			return;

		auto binary = msg->Data();
		std::string str((const char*)binary.Data, binary.Length);

		printf("%S -> %S\n%s\n", msg->CurrentProcessPath(), msg->Path(), str.c_str());
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
	config.Config[emMSGFilePostWrite] = emMSGConfigPost;
	manager.InControl(config);

	WaitForExit("���.json�ļ�д������");

	return 0;
}
//******************************************************************************
