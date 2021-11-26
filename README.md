## Table of Contents

*   [简介](#简介)
    *   [✨ 具备如下核心功能](#-具备如下核心功能)
    *   [📦 适用于如下的产品](#-适用于如下的产品)
*   [🔨 快速入门](#-快速入门)
*   [使用授权](#使用授权)
*   [加入我们](#加入我们)

## 简介

iMonitorSDK是一款为终端、云端提供系统行为监控的开发套件。帮助安全、管理、审计等行业应用可以快速实现必要功能，而不用关心底层驱动的开发、维护和兼容性问题，让其可以专注于业务开发。

iMonitorSDK同时支持进程、文件、注册表、网络、系统等的监控，使用标准稳定的实现方式，同时支持Windows（XP-Win11）、Linux、MacOS。

利用iMonitorSDK可以极低成本的实现自保护、进程拦截、勒索病毒防御、主动防御、上网行为管理等等终端安全常见的功能。

### ✨ 具备如下核心功能

- 进程、文件、注册表保护

- 进程启动、模块加载拦截，模块注入

- 文件拦截、重定向

- 网络防火墙、流量代理、协议分析
- 规则引擎、动态脚本

### 📦 适用于如下的产品

- 主动防御

- 终端管控

- 入侵检测
- 主机安全
- 零信任

- 上网行为管理

## 🔨 快速入门

示例一：进程启动拦截

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
		// 禁止进程名 cmd.exe 的进程启动
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

	WaitForExit("禁止进程名 cmd.exe 的进程启动");

	return 0;
}
```

示例二：自保护规则设置

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

	//
	// Path路径支持通配符
	//	* 表示任意n个字符
	//	? 表示任意一个字符
	//	> 用于字符串结尾，表示字符串结束或者是\\结尾，用于目录判断（比如protect> 匹配 protect 和 protect\\*）
	//
	{
		//
		// 添加进程、文件保护： 保护进程名是notepad.exe的进程不被结束、文件不被修改、删除
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeProcessPath | emProtectTypeFilePath;
		wcsncpy(rule.Path, L"*\\notepad.exe", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		//
		// 添加文件夹保护： 保护protect目录下面的文件不被外部修改、目录不被重命名、删除
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeFilePath;
		wcsncpy(rule.Path, L"*\\protect>", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		//
		// 添加注册表保护： 保护iMonitor键不被删除、修改，包括键值
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeRegPath;
		wcsncpy(rule.Path, L"*\\iMonitor>", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		//
		// 添加信任进程：可以操作被保护的进程、文件、注册表，但是进程本身不受保护
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeTrustProcess;
		wcsncpy(rule.Path, L"*taskkill*", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	WaitForExit("自保护开启中");

	manager.InControl(cxMSGUserRemoveAllProtectRule());
	manager.InControl(cxMSGUserDisableProtect());

	return 0;
}
```

示例三：sysmon

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

示例四：上网行为管理（基于网络重定向的方式实现，支持https，详细参考http_access_control例子）

![](./doc/ac.png)

更多的示例可以参考sample目录。

[详细说明请参考SDK说明文档。](./doc/README.md)

## 使用授权

> 免责说明：
>
> iMonitorSDK（以下称本SDK）只授权给为正规的企业厂商使用。禁止用于危害企业、个人安全等任何非法的场景。
>
> 本SDK带有内核驱动程序，虽然已经经过稳定测试，长期运行验证，但因为硬件、环境等原因，不可避免会存在兼容性问题，在使用本SDK前，请先在业务对应的环境系统中充分测试后再实际接入使用。
>
> 非法授权、非法使用而造成的经济损失、法律问题都于本SDK提供团队无关。
>
> 在您使用本SDK前，视为您已经知悉并且遵守此免责说明。

不同授权的功能差异：

| 功能说明           | 免费授权     | 企业授权                     | 企业定制授权 |
| ------------------ | ------------ | ---------------------------- | ------------ |
| 进程监控           | ✔            | ✔                            | ✔            |
| 文件监控           | ✔            | ✔                            | ✔            |
| 注册表监控         | ✔            | ✔                            | ✔            |
| 网络监控           | ✔            | ✔                            | ✔            |
| 自保护             | ✔            | ✔                            | ✔            |
| 网络协议代理       | ✔            | ✔                            | ✔            |
| 内核对象定制       |              | ✔                            | ✔            |
| 配置签发           |              | ✔                            | ✔            |
| 规则引擎           |              | ✔                            | ✔            |
| Javascript脚本支持 |              |                              | ✔            |
| Linux支持          |              |                              | ✔            |
| MacOS支持          |              |                              | ✔            |
| 源码               |              |                              | ✔            |
| 服务支持           | 邮件、GitHub | 邮件、GitHub、微信、远程桌面 | ✔            |

[授权请通过邮箱（iMonitor@qq.com）联系。](mailto://iMonitor@qq.com)

## 使用本SDK的产品

- [iMonitor 冰镜 - 终端行为分析系统](https://github.com/wecooperate/iMonitor)
- [iDefender 冰盾 - 终端主动防御系统](https://github.com/wecooperate/iDefender)

## 关于我们

优秀的人，做专业的事。

创信长荣科技是一家致力于为企业管理提供基础服务、一体化管理平台，力争成为企业管理入口，促进企业管理标准化、数字化的企业。我们的目标是拒绝内卷，让每个人更好的工作和生活。

我们的成员是来自金山、360、腾讯等企业的顶级优秀人才，具备深厚的技术水平。多款核心产品正在研发中，需要各方面人才的人才和资本投入。

[联系我们](mailto://iMonitor@qq.com)
