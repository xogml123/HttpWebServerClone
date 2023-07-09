#include "HttpMessage.hpp"


HttpMessage::HttpMessage(void) :
	data(),
	request_method(),
	uri("/"),
	queryString(""),
	content(),
	chunked(false)
{}

HttpMessage::HttpMessage(const HttpMessage &x)
{ *this = x; }

HttpMessage::~HttpMessage()
{}

HttpMessage&		HttpMessage::operator=(const HttpMessage &x)
{
	if (this == &x)
		return *this;
	data = x.data;
	request_method = x.request_method;
	uri = x.uri;
	queryString = x.queryString;
	content = x.content;
	chunked = x.chunked;
	return *this;
}

const char*		HttpMessage::HttpMessageParsingError::what() const throw()
{ return "incomplete http header received"; }

const char*		HttpMessage::HttpBadRequestError::what() const throw()
{ return "bad http request"; }

