[English](./README_EN.md)

## 简介

iMonitorSDK是一款为终端、云端提供系统行为监控的开发套件。

旨在帮助安全、管理、审计等行业应用可以快速实现必要功能，而不用关心底层驱动的开发、维护和兼容性问题，让其可以专注于业务开发。

iMonitorSDK的开发团队来自国内头部互联网公司，具备十多年安全开发经验，基于消息协议的通信框架，让驱动开发更加稳定、快速。内核监控使用了稳定、标准的方式实现，同时支持Windows（XP-Win11）、Linux、MacOS。

利用iMonitorSDK可以极低成本地实现自保护、进程拦截、勒索病毒防御、主动防御、上网行为管理等等终端安全常见的功能。

### ✨ 具备如下核心功能

- 进程、文件、注册表、网络各种事件监听，支持拦截禁止
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

示例五：任意时刻对进程注入动态库

```c++
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGImageLoad)
			return;

		cxMSGImageLoad* msg = (cxMSGImageLoad*)Message;

		if (!msg->IsMatchCurrentProcessName(L"notepad.exe"))
			return;

		if (msg->IsMatchPath(L"*\\kernel32.dll")) {
			msg->SetInjectDll(L"D:\\test.dll");
		}
	}
};

int main()
{
	MonitorManager manager;
	MonitorCallback callback;

	HRESULT hr = manager.Start(&callback);

	CheckSignError(hr);

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 1;
	}

	manager.InControl(cxMSGUserSetGlobalConfig());

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGImageLoad] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("模块注入：在notepad.exe启动加载kernel32.dll过程中，让其强制加载D:\\test.dll");

	return 0;
}
```

更多的示例可以参考sample目录。

[详细使用说明请参考SDK说明文档。](./doc/README.md)

## 使用授权

> 免责说明：
>
> iMonitorSDK（以下称本SDK）只授权给为正规的企业厂商使用。禁止用于危害企业、个人安全等任何非法的场景。
>
> 本SDK带有内核驱动程序，在使用本SDK前，请先在业务对应的环境系统中充分测试后再实际接入使用。
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

## 版本更新说明（LTS版本：1.0.4.0）

#### 1.0.4.0

1. 应用层返回驱动的参数添加更多设置支持

​		支持返回路径，自动插入APC注入DLL到当前进程

​		支持设置结束当前进程、线程

2. 添加PE文件的私有签名支持

​		添加配置控制只允许带私有签名的进程打开驱动，保证驱动不被利用

​		PE文件私有签名可以设置自保护标记，启动的时候自动得到自保护

3. 添加自保护等级支持（低等级自保护的进程没法打开高保护等级的进程，PE文件自保护标记默认为低等级）

4. 优化WFP的GUID生成规则，可以兼容同时安装多份驱动

5. 优化同步、异步事件的超时设置，同步、异步可以设置不同的超时

6. （经反馈还有需要完整支持XP）XP下恢复SSDT Hook的方式，用于弥补低版本标准Callback没法实现的功能

7. 驱动配置添加下列配置：enable_sign_protect，enable_sign_open_protect

**添加LTS版本支持**：

​	目前使用SDK的客户多了，为了保证稳定性，1.0.4.X版本作为LTS版本，只修复BUG，不再添加任何功能。

#### 1.0.3.0

驱动：

添加对打开进程、文件等频繁操作添加快速过滤支持
添加应用处理事件超时导致系统卡住的熔断机制
添加回话超时配置，不同的应用程序可以设置不同的超时

应用层：

优化规则过滤：添加匹配缓存、添加扩展子节点

#### 1.0.2.0

添加代理支持

添加上网行为管理功能演示

#### 1.0.1.0 

初始化版本

## 关于我们

优秀的人，做专业的事。

创信长荣科技是一家致力于为企业管理提供基础服务、一体化管理平台，力争成为企业管理入口，促进企业管理标准化、数字化的企业。



**目前创业启动资金筹备中，承接终端安全相关的各类需求，有任何商业合作、功能定制的欢迎 [联系我们](mailto://iMonitor@qq.com)**
