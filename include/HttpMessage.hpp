#ifndef HTTP_HEADER_HPP
# define HTTP_HEADER_HPP

# include "Defs.hpp"


class HttpMessage
{
	public:
		typedef std::map<std::string, std::vector<std::string> >     value_type;
	
	public:
		HttpMessage(void);
		HttpMessage(const HttpMessage &x);
		~HttpMessage();
		HttpMessage&		operator=(const HttpMessage &x);
		
	public:
		class HttpMessageParsingError : public std::exception
		{
			public:
				virtual const char*	what() const throw();
		};

		class HttpBadRequestError : public std::exception
		{
			public:
				virtual const char*	what() const throw();
		};

	private:
		value_type		data;
		std::string		request_method;
		std::string		uri;
		std::string		queryString;
		std::string		content;
		bool			chunked;


	friend class Socket;
	friend class Request;
	friend class Response;
	friend class Cgi;

};


#endif
