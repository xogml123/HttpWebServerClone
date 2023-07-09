#include "Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server() : _port(8000), _ip("127.0.0.1"), _clientMaxBodySize(100000)
{
	this->_serverName.push_back("");
}

Server::Server(const Server &src)
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server()
{
	for (size_t i = 0; i < this->_locationInfo.size(); i++)
		delete this->_locationInfo[i];

	this->_locationInfo.clear();
	this->_serverName.clear();
	this->_errorPages.clear();

	std::vector<Location *>().swap(this->_locationInfo);
	std::vector<std::string>().swap(this->_serverName);
	std::map<int, std::string>().swap(this->_errorPages);
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Server &Server::operator=(Server const &rhs)
{
	if (this != &rhs)
	{
		this->_port = rhs._port;
		this->_ip = rhs._ip;
		this->_serverName = rhs._serverName;
		this->_errorPages = rhs._errorPages;
		this->_clientMaxBodySize = rhs._clientMaxBodySize;
		this->_locationInfo = rhs._locationInfo;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Server::setAddress(const std::vector<std::string> &token)
{
	if (token.size() != 2)
		throw ParseFile::ParsingError();

	size_t pos = token[1].find(':');
	std::string port;

	if (pos == std::string::npos)
		port = token[1];
	else
	{
		this->setIp(token[1].substr(0, pos));
		port = token[1].substr(pos + 1);
	}

	if (!isNum(port) || !isIp(this->_ip))
		throw ParseFile::ParsingError();
	std::stringstream(port) >> this->_port;
	if (this->_port > std::numeric_limits<unsigned short>().max())
	{
		std::cout << "setAddress 3\n";
		throw ParseFile::ParsingError();
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void Server::setPort(const int &port)
{
	this->_port = port;
}

void Server::setIp(const std::string &ip)
{
	this->_ip = ip;
}

void Server::setServerName(const std::vector<std::string> &name)
{
	if (name.size() < 2)
	{
		std::cout << "setServerName\n";
		throw ParseFile::ParsingError();
	}

	if (name[1].empty())
		return;

	this->_serverName.assign(name.begin() + 1, name.end());
}

void Server::setErrorPages(const std::vector<std::string> &token)
{
	if (token.size() < 3)
	{
		std::cout << "setErrorPages\n";
		throw ParseFile::ParsingError();
	}

	int error_code;

	for (std::vector<std::string>::const_iterator it = token.begin() + 1; it != token.end() - 1; it++)
	{
		if (!isNum(*it))
		{
			std::cout << "setErrorPages 2\n";
			throw ParseFile::ParsingError();
		}

		std::stringstream(*it) >> error_code;

		this->_errorPages[error_code] = ROOT_PATH + token.back();
	}
}

void Server::setClientMaxBodySize(const std::vector<std::string> &token)
{
	if (token.size() != 2 || !isNum(token[1]))
	{
		std::cout << "setClientMaxBodySize\n";
		throw ParseFile::ParsingError();
	}

	std::stringstream(token[1]) >> this->_clientMaxBodySize;
}

void Server::AddNewLocationInfo(Location *location)
{
	this->_locationInfo.push_back(location);
}

const int &Server::getPort(void) const
{
	return this->_port;
}

const std::string &Server::getIp(void) const
{
	return this->_ip;
}

std::vector<std::string> &Server::getServerName(void)
{
	return this->_serverName;
}

const std::map<int, std::string> &Server::getErrorPages(void) const
{
	return this->_errorPages;
}

const int &Server::getClientMaxBodySize(void) const
{
	return this->_clientMaxBodySize;
}

const std::vector<Location *> &Server::getLocationInfo(void) const
{
	return this->_locationInfo;
}

/* ************************************************************************** */