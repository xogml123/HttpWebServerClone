#ifndef PARSEFILE_HPP
#define PARSEFILE_HPP

#include "Server.hpp"
#include "Utils.hpp"
#include "Defs.hpp"

#define FILE_EXTENSION ".conf"
#define DEFAULT_FILE "conf/default.conf"

class Server;
class Location;

enum e_state
{
	DEFAULT,
	NEW_SERVER,
	IN_SERVER,
	NEW_LOCATION,
	IN_LOCATION
};

class ParseFile
{
public:
	ParseFile();
	ParseFile(const ParseFile &src);
	~ParseFile();

	ParseFile &operator=(const ParseFile &rhs);

	bool checkFileName(const std::string &file);
	void doParsing(const std::string &file);
	void parseOneLine(std::string line);
	std::vector<std::string> makeToken(std::string line);

	void makeNewServer(const std::vector<std::string> &token);
	void makeNewLocation(const std::vector<std::string> &token);
	void AddLocationInfo(const std::vector<std::string> &token);
	void braces(const std::vector<std::string> &token);
	void directives(const std::vector<std::string> &token);
	void newServerDirective(const std::vector<std::string> &token);
	void newLocationDirective(const std::vector<std::string> &token);
	void isUnusedPort(const std::vector<std::string> &token);

	void printInfo(void);
	void deleteServerBlock(void);

	std::vector<Server *> &getServerBlock(void);
	Server *getLastServerBlock(void);
	e_state &getStatus(void);

	void AddServerBlock(void);
	void setState(const e_state &state);

	class ParsingError : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

private:
	std::vector<Server *> _serverBlock;
	e_state _state;
};

#endif