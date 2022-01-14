## Introduction

iMonitorSDK is a development kit that provides system behavior monitoring for endpoint and the cloud. Help industry applications such as security, management, and auditing can quickly implement necessary functions without worrying about underlying driver development, maintenance, and compatibility issues, allowing them to focus on business development.

The communication framework of iMonitorSDK is based on the message protocol makes the driver development more stable and faster. Kernel monitoring is implemented in a stable and standard way, and supports Windows (XP-Win11), Linux, and MacOS at the same time.

With iMonitorSDK, common terminal security functions such as self-protection, process interception, ransomware defense, active defense, and Internet behavior management can be realized at a very low cost.

### [Document](https://wecooperate.github.io/)

### ✨ Core Functions

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

Example 3: sysmon

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

[For detailed instructions, please refer to the SDK documentation. ](./doc/README.md)

## License 

> Disclaimer:
>
> iMonitorSDK (hereinafter referred to as the SDK) is only licensed to be used by regular enterprise manufacturers. It is forbidden to be used in any illegal scenes such as endangering the safety of enterprises and individuals.
>
> The economic losses and legal issues caused by illegal authorization and illegal use have nothing to do with the SDK providing team.
>
> Before you use this SDK, it is deemed that you have known and complied with this disclaimer.

Functional differences of different licenses:

| Function description | Free License | Enterprise License | Enterprise Custom License |
| -------------------- | ------------ | ------------------ | ------------------------- |
| Process Monitoring | ✔ | ✔ | ✔ |
| File Monitoring | ✔ | ✔ | ✔ |
| Registry Monitoring | ✔ | ✔ | ✔ |
| Network Monitoring | ✔ | ✔ | ✔ |
| Self-protection | ✔ | ✔ | ✔ |
| Network Protocol Proxy | ✔ | ✔ | ✔ |
| Kernel object customization | | ✔ | ✔ |
| Configuration | | ✔ | ✔ |
| Rule Engine | | ✔ | ✔ |
| Javascript script support | | | ✔ |
| Linux support | | | ✔ |
| MacOS support | | | ✔ |
| Source code | | | ✔ |
| Service Support | Mail, GitHub | Mail, GitHub, WeChat, Remote Desktop | ✔ |

[ contact via email (iMonitor@qq.com) for a licence ](mailto://iMonitor@qq.com)

## Products using this SDK

- [iMonitor - Endpoint Behavior Analysis System](https://github.com/wecooperate/iMonitor)
- [iDefender - Endpoint Active Defense System](https://github.com/wecooperate/iDefender)

## About Us

Excellent people, do professional things.

wecooperate is a company dedicated to providing basic services and integrated management platform for enterprise management, striving to become the entrance of enterprise management and promoting the standardization and digitization of enterprise management.

If you have business agency, business cooperation, function customization and other needs, [Contact Us](mailto://iMonitor@qq.com)