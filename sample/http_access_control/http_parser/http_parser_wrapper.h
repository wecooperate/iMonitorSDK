//******************************************************************************
/*++
	FileName:		http_parser_wrapper.h
	Description:

--*/
//******************************************************************************
#ifndef __http_parser_wrapper_h_904f80ae_e130_480e_b34e_d6881866110d__
#define __http_parser_wrapper_h_904f80ae_e130_480e_b34e_d6881866110d__
//******************************************************************************
#include "http_parser.h"
#include <map>
#include <string>
//******************************************************************************
class cxHTTPParserBase
{
public:
	cxHTTPParserBase(void);

public:
	virtual int on_message_begin(http_parser* parser);
	virtual int on_url(http_parser* parser, const char* data, size_t length);
	virtual int on_status(http_parser* parser, const char* data, size_t length);
	virtual int on_header_field(http_parser* parser, const char* data, size_t length);
	virtual int on_header_value(http_parser* parser, const char* data, size_t length);
	virtual int on_headers_complete(http_parser* parser);
	virtual int on_body(http_parser* parser, const char* data, size_t length);
	virtual int on_chunk_header(http_parser* parser);
	virtual int on_chunk_complete(http_parser* parser);
	virtual int on_message_complete(http_parser* parser);

protected:
	int should_keep_alive(void);
	const char* method_to_string(unsigned int method);
	const char* error_to_string(http_errno error);
	bool is_message_done(void);

public:
	void Reset(http_parser_type type = HTTP_REQUEST);
	void Pause(void);
	void Continue(void);
	size_t Parse(const char* data, size_t length);

protected:
	http_parser_settings m_parser_settings;
	http_parser m_parser;
};
//******************************************************************************
class cxHTTPParser : public cxHTTPParserBase
{
protected:
	int on_url(http_parser* parser, const char* data, size_t length) override;
	int on_header_field(http_parser* parser, const char* data, size_t length) override;
	int on_header_value(http_parser* parser, const char* data, size_t length) override;
	int on_headers_complete(http_parser* parser) override;

protected:
	void on_header(void);

protected:
	std::string m_host;
	std::string m_uri;
	std::string m_url;
	std::map<std::string, std::string> m_headers;

protected:
	std::string m_last_header_field;
	std::string m_last_header_value;
};
//******************************************************************************
#endif
