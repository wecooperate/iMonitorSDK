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
		if (Message->GetType() != emMSGSocketPostRecv)
			return;

		printf("%S ==> %S\n", Message->GetTypeName(), Message->GetFormatedString(emMSGFieldCurrentProcessPath));

		for (ULONG i = emMSGFieldCurrentProcessCommandline; i < Message->GetFieldCount(); i++) {
			printf("\t%30S : %-30S\n", Message->GetFieldName(i), Message->GetFormatedString(i));
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
	config.Config[emMSGSocketPostRecv] = emMSGConfigPost;
	manager.InControl(config);

	WaitForExit("¼à¿ØÊÕ°ü");

	return 0;
}
//******************************************************************************
// TODO
