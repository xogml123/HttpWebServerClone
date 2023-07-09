#include "Request.hpp"

Request::Request(void) :
	_constructPath(ROOT_PATH),
	_isChunked(false),
	_status(200)
{}

Request::Request(const Request &x)
{ *this = x; }

Request::~Request()
{}

Request&			Request::operator=(const Request &x)
{
	if (this == &x)
		return *this;
	_header = x._header;
	_constructPath = x._constructPath;
	_content = x._content;
	_server = x._server;
	_isChunked = x._isChunked;
	_fileInfo = x._fileInfo;
	_boundary = x._boundary;
	_status = x._status;
	return *this;
}

HttpMessage&		Request::getHeader(void)              { return this->_header ; }
const std::string&	Request::getContent(void)       const { return this->_content; }
const std::string&	Request::getConstructPath(void) const { return this->_constructPath; }
size_t				Request::getContentLength(void) const { return this->_content.size(); }
const Server*		Request::getServer(void)        const { return this->_server; }
const int&			Request::getStatus(void)        const { return this->_status; }

const Location*	Request::getLocation(void) const
{		
	
	location_type		loc;
	if (this->_server != NULL)
		loc = this->_server->getLocationInfo();
	std::string				path = ft_strcut(this->_header.uri, '?');
	size_t					pos;

	while (true)
	{
		for (location_type::const_iterator it = loc.begin(); it != loc.end(); ++it)
		{
			if (path == (*it)->getPath())
				return *it;
		}
		
		if (path == "/")
			return NULL;
		
		if (path.find_last_of('/') == 0)
			path = "/";
		else
		{
			pos = path.substr(0, path.size() - 1).find_last_of('/');
			path = path.substr(0, pos + 1);
		}
	}
	return NULL;
}

void	Request::setStatus(const int& status) {
	this->_status = status;
}

bool	Request::setRequestFirstLine(const std::string &first_line)
{
	const vector_type	line = split_string(first_line, " ");

	if (line.size() != 3)
		return false;
	
	this->getHeader().request_method = line[0];
	this->getHeader().uri = line[1];
	return true;
}

void	Request::setServer(const Server *server) { this->_server = server; }

void	Request::setContent(void)
{
	std::string					buf(this->_header.content);
	const std::string			delim(DELIMITER);
	const size_t				pos = buf.find(delim);
	
	vector_type					content_;
	vector_type::const_iterator	it;
	std::string					tmp_string = "";

	if (pos == std::string::npos)
		this->_content = "";
	else
	{
		buf = buf.substr(pos + delim.length());
		if (this->_header.chunked)
		{
			content_ = split_string(buf, NEW_LINE);
			it = content_.begin();
			if (it != content_.end() && (it + 1) != content_.end())
			{
				++it;
				for ( ; it != content_.end(); it += 2)
				{
					if ((it + 1) == content_.end())
						break ;
					tmp_string += *it;
				}
			}
			else
				tmp_string = buf;
		}
		else
			tmp_string = buf;
		
		this->_content = tmp_string;
	}
}

void	Request::setConstructPath(void)
{
	const Location	*loc = this->getLocation();
	std::string			uriPath = ft_strcut(this->_header.uri, '?');
	
	std::string						  	path_tmp("");
	std::string							index_tmp;
	Server::tokens_type::const_iterator	idx;
	
	if (loc != NULL)
	{
		if (!((loc->getRoot()).empty()))
		{
			path_tmp += loc->getRoot();
			if (path_tmp[path_tmp.size() - 1] != '/')
				path_tmp += uriPath.substr(loc->getPath().size() - 1);
			else
				path_tmp += uriPath.substr(loc->getPath().size());
		}
		else
			path_tmp += uriPath;

		if (isDir(ROOT_PATH + path_tmp))
		{
			if (path_tmp[path_tmp.size() - 1] != '/')
				path_tmp += "/";
			for (idx = loc->getIndex().begin(); idx != loc->getIndex().end(); ++idx)
			{
				index_tmp = path_tmp + *idx;
				if (is_valid_path(ROOT_PATH + index_tmp))
				{
					path_tmp = index_tmp;
					break ;
				}
			}
		}
	}
	else
	{
		path_tmp += uriPath;
	}
	
	this->_constructPath += path_tmp;
}

void	Request::setConstructPath(const std::string &path)
{
	this->_constructPath = path;
}

void	Request::setHeaderData(const std::string& line_)
{
	static pair_type	option[] = {
		std::make_pair("Host",						" " ),
		std::make_pair("Origin",					""  ),
		std::make_pair("Content-Type",				""  ),
		std::make_pair("Accept-Encoding",			", "),
		std::make_pair("Connection",				" " ),
		std::make_pair("Upgrade-Insecure-Requests",	""  ),
		std::make_pair("Accept",					"," ),
		std::make_pair("Transfer-Encoding",         ", "),
		std::make_pair("User-Agent",				""  ),
		std::make_pair("Referer",					" " ),
		std::make_pair("Accept-Language",			" " )
	};
	static info_type	options(option, option + sizeof(option) / sizeof(pair_type));
	static std::string	separator = ": ";
	const size_t		pos = line_.find(separator);
	pair_type			mapped;
	
	if (pos == std::string::npos)
		return ;
	
	mapped = std::make_pair(line_.substr(0, pos), line_.substr(pos + separator.length()));

	for (info_type::const_iterator opt_it = options.begin(); opt_it != options.end(); ++opt_it)
	{
		if (opt_it->first == mapped.first)
		{
			this->_header.data[mapped.first] = split_string(mapped.second, opt_it->second);
		}
	}
}

void	Request::setChunked(void)
{
	const vector_type			transfert_encoding = _header.data["Transfer-Encoding"];
	vector_type::const_iterator	it = transfert_encoding.begin();

	_header.chunked = false;
	for ( ; it != transfert_encoding.end(); ++it)
	{
		if (*it == "chunked")
		{
			_header.chunked = true;
			break ;
		}
	}
}

const Request::info_type&	Request::getFileInfo(void) const { return this->_fileInfo; }
const std::string&			Request::getBoundary(void) const { return this->_boundary; }

bool	Request::checkIsUploadCase(void) {
	std::string	toFind[] = {"POST", "multipart/form-data", "boundary", "filename", ""};
	std::string	headerBuf(_header.content);
	size_t		pos;

	for (size_t i = 0; toFind[i].empty() == false; ++i) {
		if ((pos = headerBuf.find(toFind[i])) == std::string::npos)
			return false;
	}

	std::string	boundary = "boundary=";
	_boundary = headerBuf;
	if ((pos = _boundary.find(boundary)) != std::string::npos) {
		_boundary.erase(0, pos + boundary.length());
		if ((pos = _boundary.find(NEW_LINE)) != std::string::npos) {
			_boundary.erase(pos);
			_boundary.insert(0, "--");
		}
		else
			return false;
	}
	else
		return false;
	return true;
}

bool	Request::parseFile(void) {
	if (false == checkIsUploadCase()) {
		return false;
	}

	std::string toParse = this->getContent();
	std::string key[] = {"filename=\"", "\"", "Content-Type", NEW_LINE, DELIMITER, this->getBoundary() + "--" NEW_LINE};

	std::string fileName;
	std::string fileContent;

	size_t begin;
	size_t end;

	while (true) {
		if ((begin = toParse.find(key[FN])) != std::string::npos)
			toParse.erase(0, begin + key[FN].length());
		if ((end = toParse.find(key[DQ])) != std::string::npos)
			fileName = toParse.substr(0, end);

		if ((begin = toParse.find(key[CT])) != std::string::npos)
			toParse.erase(0, begin + key[CT].length());
		if ((begin = toParse.find(key[DRN])) != std::string::npos)
			toParse.erase(0, begin + key[DRN].length());
		if ((end = toParse.find(key[RN])) != std::string::npos)
			fileContent = toParse.substr(0, end);

		if(false == fileName.empty())
			_fileInfo.insert(std::make_pair(fileName, fileContent));
		toParse.erase(0, fileContent.length() + key[RN].length());
		if (toParse == key[LAST_BOUNDARY])
			break ;
		else
			toParse.erase(0, this->getBoundary().length() + key[RN].length());
	}
	return true;
}

void	Request::print(void) const
{
	size_t	len = this->_header.uri.length();
	size_t	sp	= 42 - this->_header.request_method.length();

	std::cout	<< this->_header.request_method << " "
				<< "http://" << (this->_server->getIp() == "127.0.0.1" ? "localhost" : this->_server->getIp())
				<< ":" << this->_server->getPort();
	if (len > sp) {
		std::cout << this->_header.uri.substr(0, 10) << "[...]" << this->_header.uri.substr(len - 10) << std::setw(sp - 25) << "";
	}
	else
		std::cout << this->_header.uri << std::setw(sp - len) << "";
}