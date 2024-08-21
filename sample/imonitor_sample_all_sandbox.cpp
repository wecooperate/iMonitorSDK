//******************************************************************************
/*++
	Description:

	�������ļ�ɳ��ʹ��ʾ����
		notepad.exe ������ɳ�䣬�޸ĵ��ļ����Զ��ض���ɳ������

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
	[
        {
            "sandbox_name" : "test",
            "sandbox_root" : "C:\\sandbox",
			"processes": ["*\\notepad.exe"],
			"include_child_processes": true,
			"include_exist_processes": true
        }
    ]
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
	hr = manager.SetRules(emUserSetSandboxRules, rules.c_str());

	if (hr != S_OK) {
		printf("set rules failed = %08X\n", hr);
		return 0;
	}

	WaitForExit("��notepad.exe���뵽ɳ��ִ�С�\n"
				"\tע�⣺�˹��������ã��������Ҫ�ָ���Ҫ�Ƴ�����\n"
				"\t��������Ƴ������˳���");

	manager.InControl(cxMSGUserRemoveSandboxRules());

	return 0;
}
//******************************************************************************
