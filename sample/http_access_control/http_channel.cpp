//******************************************************************************
/*++
	FileName:		http_channel.cpp
	Description:

--*/
//******************************************************************************
#include "http_channel.h"
#include <sstream>
//******************************************************************************
void HTTPChannel::OnCreate(IMonitorAgentChannel* Channel)
{
	m_channel = Channel;

	Reset(HTTP_REQUEST);
}

void HTTPChannel::OnLocalReceive(const char* Data, ULONG Length)
{
	if (m_parse_failed)
		return;

	size_t parser_length = Parse(Data, Length);

	if (parser_length != Length)
		m_parse_failed = true;
}

void HTTPChannel::OnLocalSSLHello(const char* ServerName)
{
	m_ssl = true;
}

void HTTPChannel::OnClose(void)
{
	m_channel = nullptr;
}

int HTTPChannel::on_headers_complete(http_parser* parser)
{
	cxHTTPParser::on_headers_complete(parser);

	Trace();
	ProcessRule();

	return 0;
}

int HTTPChannel::on_message_complete(http_parser* parser)
{
	Reset(HTTP_REQUEST);

	return 0;
}

void HTTPChannel::Trace(void)
{
	std::string url = m_url.length() < 100 ? m_url : m_url.substr(0, 100 - 3) + "...";

	printf("[%6d] %4s %s://%s\n",
		m_channel->LocalGetProcessId(),
		method_to_string(m_parser.method),
		m_ssl ? "https" : "http",
		url.c_str());
}

void HTTPChannel::ProcessRule(void)
{
	if (m_host.find("git") == std::string::npos)
		return;

	static std::string disable_response = R"(
<!DOCTYPE html>
<html>
<head>
    <title>iMonitorSDK - 上网行为管理</title>
</head>
<body>
    <div style="
        text-align:center;
        margin:100px auto;
        width:400px;
        color:white;
        background:crimson;
        height:50px;
        line-height:50px;
        font-size:20px;">
        管理员禁止您访问该网站
    </div>

    <div style="
    text-align:center;
    position: fixed;
    width: 100%;
    color:grey;
    bottom:10px; ">
        Powered by iMonitorSDK
    </div>
</body>
</html>
)";

	FinishRequest(http_status::HTTP_STATUS_OK, disable_response);
}

void HTTPChannel::FinishRequest(http_status status, const std::string& data)
{
	std::stringstream ss;

	ss << "HTTP/1.1 " << status << http_status_str(status) << "\r\n";
	ss << "Connection: close\r\nContent-Length: " << data.length() << "\r\n\r\n";
	ss << data;

	std::string response = ss.str();

	m_channel->LocalSend(response.c_str(), response.length());
	m_channel->Close();
}

void HTTPChannelManager::OnCreate(IMonitorAgentChannel* Channel)
{
	HTTPChannel* http_channel = new HTTPChannel;

	Channel->SetContext(http_channel);

	http_channel->OnCreate(Channel);
}

void HTTPChannelManager::OnLocalReceive(IMonitorAgentChannel* Channel, const char* Data, size_t Length)
{
	HTTPChannel* http_channel = static_cast<HTTPChannel*>(Channel->GetContext());

	if (!http_channel)
		return;

	http_channel->OnLocalReceive(Data, (ULONG)Length);
}

bool HTTPChannelManager::OnLocalSSLHello(IMonitorAgentChannel* Channel, const char* ServerName)
{
	HTTPChannel* http_channel = static_cast<HTTPChannel*>(Channel->GetContext());

	if (!http_channel)
		return true;

	http_channel->OnLocalSSLHello(ServerName);

	return true;
}

void HTTPChannelManager::OnClose(IMonitorAgentChannel* Channel)
{
	HTTPChannel* http_channel = static_cast<HTTPChannel*>(Channel->GetContext());

	if (!http_channel)
		return;

	http_channel->OnClose();

	delete http_channel;
}
