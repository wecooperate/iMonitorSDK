//******************************************************************************
/*++
	Description:

	�ں˹������棨����ֱ��������������Ч��ʹ��ʾ����
		һЩ̫Ƶ�����¼�������׵�Ӧ�ò�ִ�й������棬Ч�ʻ�Ƚϵͣ���������Ϳ���ʹ���ں˼���Ĺ�������

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* msg) override
	{
	}
};
//******************************************************************************
std::string InitRules(void)
{
	return R"(
{
    "name" : "default",
    "description" : "default rule group",
    "rules" : [
        {
            "name" : "block notepad start",
            "action" : 1,
            "event" : "ProcessCreate",
            "matcher" : {
                "or" : [
                    {"match" : ["Path", "*\\notepad.exe"]},
                    {"match" : ["Path", "*\\notepad++.exe"]}
                ]
            }
        }
    ]
}
)";
}
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

	std::string rules = InitRules();
	manager.SetRules(emUserSetMSGRules, rules.c_str());

	WaitForExit("�����ں˹��򣺽�ֹnotepad�Ľ���������\n"
				"\tע�⣺�˹��������ã��������Ҫ�ָ���Ҫ�Ƴ�����\n"
				"\t��������Ƴ������˳���");

	manager.InControl(cxMSGUserRemoveMSGRules());

	return 0;
}
//******************************************************************************
