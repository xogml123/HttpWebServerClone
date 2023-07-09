#include "Webserv.hpp"


Webserv::Webserv(ParseFile& parseFile) :
	_servers(parseFile.getServerBlock()),
	_socks(NULL)
{}

Webserv::~Webserv()
{
	if (_socks != NULL)
	{
		delete [] _socks;
		_socks = NULL;
	}
}



size_t			Webserv::serverSize(void) const
{ return this->_servers.size(); }

const Server&	Webserv::getServer(int i) const
{ return *(this->_servers[i]); }

size_t			Webserv::countSocket() const
{
	size_t	count = _servers.size();

	for (size_t i = 0; i < _servers.size(); ++i)
	{
		for (size_t j = 0; j < i; ++j)
		{
			if (_servers[i]->getIp() == _servers[j]->getIp() && _servers[i]->getPort() == _servers[j]->getPort())
			{
				--count;
				break ;
			}
		}
	}
	return count;
}

std::vector<Server *>	Webserv::selectServers(size_t& index)
{
	std::vector<Server *>	blocks;
	bool					firstOccur = false;

	while (false == firstOccur)
	{
		firstOccur = true;
		for (size_t j = 0; j < index; ++j)
		{
			if (_servers[index]->getIp() == _servers[j]->getIp() &&
				_servers[index]->getPort() == _servers[j]->getPort())
			{
				firstOccur = false;
				if (index == _servers.size())
					return blocks;
				++index;
				break ;
			}
		}
	}
	
	blocks.push_back(_servers[index]);

	for (size_t i = index + 1; i < _servers.size(); i++)
	{
		if (_servers[index]->getIp() == _servers[i]->getIp() &&
			_servers[index]->getPort() == _servers[i]->getPort())
		{
			blocks.push_back(_servers[i]);
		}
	}
    
	return blocks;
}

void Webserv::createServers(void)
{
	const size_t	n = countSocket();
	Socket			cur;

	_socks = new Socket[n];
	for (size_t i = 0, j = 0; j < n; ++i, ++j)
	{
		_socks[j] = Socket(selectServers(i));
		_socks[j].startSocket();
	}

	Kqueue	_kqueue(_socks, n);
	_kqueue.startKqueue();
}

const char*		Webserv::ParsingError::what() const throw()
{ return "file not served by webserv"; }


