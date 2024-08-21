//******************************************************************************
/*++
	FileName:		http_parser_wrapper.cpp
	Description:

--*/
//******************************************************************************
#include "http_parser_wrapper.h"
//******************************************************************************
#define HTTP_DEFINE_CALLBACK(name)                                \
	static int http_##name##(http_parser * parser)                \
	{                                                             \
		return ((cxHTTPParserBase*)parser->data)->##name(parser); \
	}

#define HTTP_DEFINE_CALLBACK_WITH_DATA(name)                                     \
	static int http_##name##(http_parser * parser, const char* data, size_t length) \
	{                                                                            \
		return ((cxHTTPParserBase*)parser->data)->##name(parser, data, length);     \
	}

HTTP_DEFINE_CALLBACK(on_message_begin);
HTTP_DEFINE_CALLBACK_WITH_DATA(on_url);
HTTP_DEFINE_CALLBACK_WITH_DATA(on_status);
HTTP_DEFINE_CALLBACK_WITH_DATA(on_header_field);
HTTP_DEFINE_CALLBACK_WITH_DATA(on_header_value);
HTTP_DEFINE_CALLBACK(on_headers_complete);
HTTP_DEFINE_CALLBACK_WITH_DATA(on_body);
HTTP_DEFINE_CALLBACK(on_message_complete);
HTTP_DEFINE_CALLBACK(on_chunk_header);
HTTP_DEFINE_CALLBACK(on_chunk_complete);

cxHTTPParserBase::cxHTTPParserBase(void)
{
	http_parser_settings_init(&m_parser_settings);

	m_parser_settings.on_message_begin = http_on_message_begin;
	m_parser_settings.on_url = http_on_url;
	m_parser_settings.on_status = http_on_status;
	m_parser_settings.on_header_field = http_on_header_field;
	m_parser_settings.on_header_value = http_on_header_value;
	m_parser_settings.on_headers_complete = http_on_headers_complete;
	m_parser_settings.on_body = http_on_body;
	m_parser_settings.on_message_complete = http_on_message_complete;
	m_parser_settings.on_chunk_header = http_on_chunk_header;
	m_parser_settings.on_chunk_complete = http_on_chunk_complete;

	m_parser.data = this;
}

int cxHTTPParserBase::on_message_begin(http_parser* parser)
{
	return 0;
}

int cxHTTPParserBase::on_url(http_parser* parser, const char* data, size_t length)
{
	return 0;
}

int cxHTTPParserBase::on_status(http_parser* parser, const char* data, size_t length)
{
	return 0;
}

int cxHTTPParserBase::on_header_field(http_parser* parser, const char* data, size_t length)
{
	return 0;
}

int cxHTTPParserBase::on_header_value(http_parser* parser, const char* data, size_t length)
{
	return 0;
}

int cxHTTPParserBase::on_headers_complete(http_parser* parser)
{
	return 0;
}

int cxHTTPParserBase::on_body(http_parser* parser, const char* data, size_t length)
{
	return 0;
}

int cxHTTPParserBase::on_message_complete(http_parser* parser)
{
	return 0;
}

int cxHTTPParserBase::on_chunk_header(http_parser* parser)
{
	return 0;
}

int cxHTTPParserBase::on_chunk_complete(http_parser* parser)
{
	return 0;
}

int cxHTTPParserBase::should_keep_alive(void)
{
	return http_should_keep_alive(&m_parser);
}

const char* cxHTTPParserBase::method_to_string(unsigned int method)
{
	return http_method_str((http_method)method);
}

const char* cxHTTPParserBase::error_to_string(http_errno error)
{
	return http_errno_name(error);
}

bool cxHTTPParserBase::is_message_done(void)
{
	return http_body_is_final(&m_parser) != 0;
}

void cxHTTPParserBase::Pause(void)
{
	http_parser_pause(&m_parser, 1);
}

void cxHTTPParserBase::Continue(void)
{
	http_parser_pause(&m_parser, 0);
}

void cxHTTPParserBase::Reset(http_parser_type type)
{
	http_parser_init(&m_parser, type);
}

size_t cxHTTPParserBase::Parse(const char* data, size_t length)
{
	return http_parser_execute(&m_parser, &m_parser_settings, data, length);
}

int cxHTTPParser::on_url(http_parser* parser, const char* data, size_t length)
{
	m_uri.append(data, length);

	return 0;
}

int cxHTTPParser::on_header_field(http_parser* parser, const char* data, size_t length)
{
	on_header();

	m_last_header_field.append(data, length);

	return 0;
}

int cxHTTPParser::on_header_value(http_parser* parser, const char* data, size_t length)
{
	m_last_header_value.append(data, length);

	return 0;
}

int cxHTTPParser::on_headers_complete(http_parser* parser)
{
	on_header();

	m_url = m_host + m_uri;

	return 0;
}

void cxHTTPParser::on_header(void)
{
	if (m_last_header_value.empty())
		return;

	if (m_last_header_field == "Host") {
		m_host = m_last_header_value;
	}

	m_headers.emplace(std::make_pair(std::move(m_last_header_field), std::move(m_last_header_value)));
}
