#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Defs.hpp"
# include "Cgi.hpp"
# include "Location.hpp"

class Request;
class Location;
class Cgi;

class Response
{

	public:
		typedef std::map<std::string, std::string>             info_type;
		typedef std::pair<int, std::string>                    status_type;

	public:
		Response(Request *);
		~Response();

	private:
		Response(void);
		Response(const Response &);
		Response&			operator=(const Response &);

	public:
		const std::string&  getHeader(void) const;
		const std::string&  getContent(void) const;
		size_t				getContentLength(void) const;
		const status_type&  getStatus(void) const;
		bool				getCgiStatus(void) const;
		int					getCgiStep(void) const;
		
	
		const std::string   generateAutoindexPage(std::string const &) const;
		void		        setContent(const std::string &);
		void		        setHeader(void);
		void		        setStatus(const status_type &);
		void		        setStatus(int);
		void                setErrorContent(void);
		
		void				methodGet(const std::string &);
		void				methodPost(void);
		void				methodDelete(void);
		bool                isMethodAllowed(const std::string &);
		void				cgi(void);
		
		bool				uploadFile(void);

		void				printStatus(void) const;

	private:
		std::string			_header;
		std::string			_content;
		status_type			_status;
		Request*			_request;
		Cgi*				_cgi;
		const Location*		_location;
		bool				_cgiStatus;
	
};


#endif
