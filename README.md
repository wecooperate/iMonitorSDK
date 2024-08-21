[中文](./README_zh.md)

## Introduction

iMonitorSDK is a development kit that provides system behavior monitoring for endpoint and the cloud security. 

It is designed to help industrial applications such as security, endpoint management, and auditing can quickly implement necessary functions without worrying about the development, maintenance and compatibility of kernel drivers, allowing them to focus on business development.

iMonitorSDK uses a communication framework based on message protocol to make driver development more stable and fast. All monitoring is implemented in a stable, standard way and supports Windows from XP to Win11. Linux and MacOS are also planning support.

Using iMonitorSDK, you can realize self-protection, process interception, ransomware defense, active defense, Internet behavior management and other endpoint security functions at a very low cost.

### [Documents](https://imonitorsdk.com/)

### ✨ Core Functions

- Process, File, Registry, Network real-time monitoring, support interception and prohibition

- Process, File, Registry Protection

- Process startup, module loading interception, module injection

- File interception and redirection

- Network firewall, traffic proxy, protocol analysis
- Rule engine, script support

### 📦 Applicable to the following products

- Endpoint Security Management System
- EDR
- HIPS
- Cloud Security
- Zero trust
- Internet Access Control

### 🔨 Quick start

Example 1: Process start interception

```c++
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGProcessCreate)
			return;

		cxMSGProcessCreate* msg = (cxMSGProcessCreate*)Message;

		//
		// Block the process of the process name cmd.exe from starting
		//

		if (msg->IsMatchPath(L"*\\cmd.exe"))
			msg->SetBlock();
	}
};

int main()
{
	MonitorManager manager;
	MonitorCallback callback;

	HRESULT hr = manager.Start(&callback);

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 0;
	}

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGProcessCreate] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("Block the process of the process name cmd.exe from starting");

	return 0;
}
```

Example 2: Self-protection

```c++
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{}
};

int main()
{
	MonitorManager manager;
	MonitorCallback callback;

	HRESULT hr = manager.Start(&callback);

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 0;
	}

	manager.InControl(cxMSGUserEnableProtect());

	{
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeProcessPath | emProtectTypeFilePath;
		wcsncpy(rule.Path, L"*\\notepad.exe", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeFilePath;
		wcsncpy(rule.Path, L"*\\protect>", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeRegPath;
		wcsncpy(rule.Path, L"*\\iMonitor>", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeTrustProcess;
		wcsncpy(rule.Path, L"*taskkill*", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	WaitForExit("SelfProtect");

	manager.InControl(cxMSGUserRemoveAllProtectRule());
	manager.InControl(cxMSGUserDisableProtect());

	return 0;
}
```

Example 3: Sysmon

```c++
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* msg) override
	{
		printf("%S ==> %S\n", msg->GetTypeName(), msg->GetFormatedString(emMSGFieldCurrentProcessPath));

		for (ULONG i = emMSGFieldCurrentProcessCommandline; i < msg->GetFieldCount(); i++) {
			printf("\t%30S : %-30S\n", msg->GetFieldName(i), msg->GetFormatedString(i));
		}
	}
};

int main()
{
	MonitorManager manager;
	MonitorCallback callback;

	HRESULT hr = manager.Start(&callback);

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 0;
	}

	cxMSGUserSetMSGConfig config;
	for (int i = 0; i < emMSGMax; i++) {
		config.Config[i] = emMSGConfigPost;
	}
	manager.InControl(config);

	WaitForExit("");

	return 0;
}
```

<img src="./doc/sysmon.gif" />

Example 4: Internet Access Control (based on network redirection, support https, refer to http_access_control example for details)

![](./doc/ac.png)

More examples can refer to the sample directory.

## Products using this SDK

- [iMonitor - Endpoint Behavior Analysis System](https://github.com/wecooperate/iMonitor)
- [iDefender - Endpoint Defense System](https://github.com/wecooperate/iDefender)

## License 
[ contact via email (admin@trustsing.com) for a licence ](mailto://admin@trustsing.com)

