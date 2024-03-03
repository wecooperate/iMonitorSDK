//******************************************************************************
/*++
	FileName:		HttpChannel.h
	Description:

--*/
//******************************************************************************
#ifndef __HttpChannel_h_8986995e_95dc_420a_a755_c54d0821c3ab__
#define __HttpChannel_h_8986995e_95dc_420a_a755_c54d0821c3ab__
//******************************************************************************
#include <string>
#include "imonitor_sample.h"
#include "http_parser/http_parser_wrapper.h"
//******************************************************************************
class HTTPChannel : public cxHTTPParser
{
public:
	void OnCreate(IMonitorAgentChannel* Channel);
	void OnLocalReceive(const char* Data, ULONG Length);
	void OnLocalSSLHello(const char* ServerName);
	void OnClose(void);

public:
	int on_headers_complete(http_parser* parser) override;
	int on_message_complete(http_parser* parser) override;

protected:
	void Trace(void);
	void ProcessRule(void);
	void FinishRequest(http_status status, const std::string& data);

protected:
	IMonitorAgentChannel* m_channel = NULL;
	bool m_parse_failed = false;
	bool m_ssl = false;
};
//******************************************************************************
class HTTPChannelManager : public IMonitorAgentCallback
{
public:
	void OnCreate(IMonitorAgentChannel* Channel) override;
	void OnLocalReceive(IMonitorAgentChannel* Channel, const char* Data, size_t Length) override;
	bool OnLocalSSLHello(IMonitorAgentChannel* Channel, const char* ServerName) override;
	void OnClose(IMonitorAgentChannel* Channel) override;
};
//******************************************************************************
#endif
