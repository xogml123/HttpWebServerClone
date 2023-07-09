#ifndef SERVER_HPP
#define SERVER_HPP

#include "Defs.hpp"
#include "Location.hpp"
#include "ParseFile.hpp"


class ParseFile;
class Location;

class Server
{

public:
	typedef std::vector<std::string>  tokens_type;

	Server();
	Server(const Server &src);
	~Server();

	Server &operator=(const Server &rhs);

	void runServer();

	void setAddress(const std::vector<std::string> &token);
	void setPort(const int &port);
	void setIp(const std::string &ip);
	void setServerName(const std::vector<std::string> &token);
	void setErrorPages(const std::vector<std::string> &token);
	void setClientMaxBodySize(const std::vector<std::string> &token);
	void AddNewLocationInfo(Location *location);

	const int &getPort(void) const;
	const std::string &getIp(void) const;
	std::vector<std::string> &getServerName(void);
	const std::map<int, std::string> &getErrorPages(void) const;
	const int &getClientMaxBodySize(void) const;
	const std::vector<Location *> &getLocationInfo(void) const;

private:
	int _port;
	std::string _ip;
	std::vector<std::string> _serverName;
	std::map<int, std::string> _errorPages;
	int _clientMaxBodySize;
	std::vector<Location *> _locationInfo;
};

#endif 