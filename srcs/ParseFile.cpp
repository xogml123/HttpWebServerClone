#include "ParseFile.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ParseFile::ParseFile() : _serverBlock(), _state(DEFAULT) {}

ParseFile::ParseFile(const ParseFile &src)
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ParseFile::~ParseFile()
{
	this->deleteServerBlock();
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ParseFile &ParseFile::operator=(const ParseFile &rhs)
{
	if (this != &rhs)
	{
		this->_serverBlock = rhs._serverBlock;
		this->_state = rhs._state;
	}

	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool ParseFile::checkFileName(const std::string &file)
{
	if (file.length() < 5)
		return false;

	size_t pos = file.rfind(".conf");

	if (pos == std::string::npos || pos != file.length() - 5)
		return false;

	return true;
}

void ParseFile::doParsing(const std::string &file)
{
	std::fstream os;
	std::string line;

	os.open(file);

	if (!os)
	{
		std::cout << "fileOpen\n";
		throw ParsingError();
	}

	while (std::getline(os, line))
		parseOneLine(line);

	if (this->getStatus() != DEFAULT)
	{
		std::cout << "getStatus 1\n";
		throw ParsingError();
	}

	os.close();
}

void ParseFile::parseOneLine(std::string line)
{
	size_t pos = line.find("#") == std::string::npos ? line.length() : line.find("#");
	line = line.substr(0, pos);
	std::vector<std::string> token = makeToken(line);

	if (!token.empty())
	{
		if (token[0] == "server")
			makeNewServer(token);
		else if (token[0] == "location")
			makeNewLocation(token);
		else if (token[0] == "{" || token[0] == "}")
			braces(token);
		else
		{
			size_t pos = token.back().find(';');

			if (pos != std::string::npos)
				token.back() = token.back().substr(0, pos);

			directives(token);
		}
	}
}

std::vector<std::string> ParseFile::makeToken(std::string line)
{
	std::vector<std::string> tokens;

	size_t pos = (line.find('\t') < line.find(' ')) ? line.find('\t') : line.find(' ');

	while (pos != std::string::npos)
	{
		std::string str = line.substr(0, pos);

		if (!str.empty())
			tokens.push_back(str);

		line.erase(0, pos + 1);

		pos = (line.find('\t') < line.find(' ')) ? line.find('\t') : line.find(' ');
	}

	if (line[0])
		tokens.push_back(line);

	return tokens;
}

void ParseFile::makeNewServer(const std::vector<std::string> &token)
{
	if (token.size() != 1 || this->getStatus() != DEFAULT)
	{
		std::cout << "makeNewServer 1\n";
		throw ParsingError();
	}

	this->AddServerBlock();
	this->setState(NEW_SERVER);
}

void ParseFile::makeNewLocation(const std::vector<std::string> &token)
{
	if (this->getStatus() != IN_SERVER)
	{
		std::cout << "makeNewLocation 1\n";
		throw ParsingError();
	}

	this->AddLocationInfo(token);
	this->setState(NEW_LOCATION);
}

void ParseFile::AddLocationInfo(const std::vector<std::string> &token)
{
	Location *location;

	if (token.size() != 2 || token[1].find(';') != std::string::npos)
	{
		std::cout << "AddLocationInfo 1\n";
		throw ParsingError();
	}

	location = new Location();

	location->setPath(token[1]);
	this->getLastServerBlock()->AddNewLocationInfo(location);
}

void ParseFile::braces(const std::vector<std::string> &token)
{
	if (token.size() != 1)
	{
		std::cout << "braces 1\n";
		throw ParsingError();
	}

	if (token[0] == "{")
	{
		if (this->getStatus() == NEW_SERVER)
			this->setState(IN_SERVER);
		else if (this->getStatus() == NEW_LOCATION)
			this->setState(IN_LOCATION);
		else
		{
			std::cout << "braces 2\n";
			throw ParsingError();
		}
	}
	else
	{
		if (this->getStatus() == IN_LOCATION)
			this->setState(IN_SERVER);
		else if (this->getStatus() == IN_SERVER)
			this->setState(DEFAULT);
		else
		{
			std::cout << "braces 3\n";
			throw ParsingError();
		}
	}
}

void ParseFile::directives(const std::vector<std::string> &token)
{
	if (this->getStatus() == IN_SERVER)
		newServerDirective(token);
	else if (this->getStatus() == IN_LOCATION)
		newLocationDirective(token);
	else
	{
		std::cout << "directives\n";
		throw ParsingError();
	}
}

void ParseFile::newServerDirective(const std::vector<std::string> &token)
{
	if (token.empty())
		return;

	std::string directives[] = {
		"listen",
		"server_name",
		"error_page",
		"client_max_body_size",
		""};

	void (Server::*ptr[])(const std::vector<std::string> &) = {
		&Server::setAddress,
		&Server::setServerName,
		&Server::setErrorPages,
		&Server::setClientMaxBodySize};

	for (size_t i = 0; !directives[i].empty(); ++i)
	{
		if (token[0] == directives[i])
		{
			(*this->getLastServerBlock().*ptr[i])(token);
			return;
		}
	}

	std::cout << "newServerDirective\n";
	throw ParsingError();
}

void ParseFile::newLocationDirective(const std::vector<std::string> &token)
{
	if (token.size() < 2)
	{
		std::cout << "newLocationDirective\n";
		throw ParsingError();
	}

	std::string directives[] = {
		"limit_except",
		"return",
		"root",
		"index",
		"autoindex",
		"cgi_pass",
		"upload_store",
		""};

	void (Location::*ptr[])(const std::vector<std::string> &) = {
		&Location::setMethods,
		&Location::setReturn,
		&Location::setRoot,
		&Location::setIndex,
		&Location::setAutoIndex,
		&Location::setCgi,
		&Location::setUploadStore};

	for (size_t i = 0; !directives[i].empty(); ++i)
		if (token[0] == directives[i])
		{
			(*this->getLastServerBlock()->getLocationInfo().back().*ptr[i])(token);

			return;
		}
	std::cout << token[0] << "\n";
	std::cout << "newLocationDirective 2\n";
	throw ParsingError();
}

void ParseFile::deleteServerBlock(void)
{
	this->_serverBlock.clear();
	std::vector<Server *>().swap(this->_serverBlock);
}

void ParseFile::printInfo(void)
{
	for (size_t i = 0; i < this->getServerBlock().size(); i++)
	{
		std::cout << "======= serverBlock[" << i << "] =======\n";

		std::cout << "IP : " << this->_serverBlock[i]->getIp() << "\n";
		std::cout << "Port : " << this->_serverBlock[i]->getPort() << "\n";

		std::cout << "Server name list {";
		std::vector<std::string> tmp = this->_serverBlock[i]->getServerName();
		for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); ++it)
			std::cout << *it << ", ";
		std::cout << "}\n";

		std::cout << "Error page list :";
		std::map<int, std::string> tmp2 = this->_serverBlock[i]->getErrorPages();
		for (std::map<int, std::string>::iterator it = tmp2.begin(); it != tmp2.end(); ++it)
			std::cout << "{" << it->first << ", " << it->second << "},";
		std::cout << "\n";

		std::cout << "Client Max Body Size : " << this->_serverBlock[i]->getClientMaxBodySize() << "\n";
	}
}

const char *ParseFile::ParsingError::what() const throw()
{
	return "Unavailable Files";
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::vector<Server *> &ParseFile::getServerBlock(void)
{
	return this->_serverBlock;
}

Server *ParseFile::getLastServerBlock(void)
{
	return this->_serverBlock.back();
}

e_state &ParseFile::getStatus(void)
{
	return this->_state;
}

void ParseFile::AddServerBlock(void)
{
	this->_serverBlock.push_back(new Server());
}

void ParseFile::setState(const e_state &state)
{
	this->_state = state;
}

/* ************************************************************************** */