#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "Defs.hpp"
# include "HttpMessage.hpp"
# include "Server.hpp"

enum	e_uploadKey
{
	FN,
	DQ,
	CT,
	RN,
	DRN,
	LAST_BOUNDARY
};

class Response;
class Socket;
class Location;
class Server;

class Request
{
	public:
		typedef std::map<std::string, std::string>             info_type;
		typedef std::vector<std::string>                       vector_type;
		typedef std::vector<Location *>                        location_type;
		typedef std::pair<std::string, std::string>            pair_type;
	
	public:
		Request(const Request &);
		Request(void);
		~Request();
		Request&			operator=(const Request &);

	private:

	public:
		HttpMessage&		getHeader(void);
		const std::string&	getContent(void) const;
		const std::string&	getConstructPath(void) const;
		size_t				getContentLength(void) const;
		const Server*		getServer(void) const;
		const Location*		getLocation(void) const;
		const int&			getStatus(void) const;
		
		
		bool				setRequestFirstLine(const std::string &);
		void				setConstructPath(void);
		void				setConstructPath(const std::string &);
		void				setContent(void);
		void				setHeaderData(const std::string &);
		void				setChunked(void);
		void				setServer(const Server *);
		void				setStatus(const int &);

		const info_type&	getFileInfo(void) const;
		bool				checkIsUploadCase(void);
		const std::string&	getBoundary(void) const;
		bool				parseFile(void);

		void				print(void) const;

	private:
		HttpMessage			_header;
		std::string			_constructPath;
		std::string			_content;
		const Server		*_server;
		bool				_isChunked;
	
		info_type			_fileInfo;
		std::string			_boundary;
		int					_status;
	
};


#endif
