#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "ParseFile.hpp"
#include "Response.hpp"
#include "Defs.hpp"

#define AUTOINDEX_OFF false
#define AUTOINDEX_ON true

class ParseFile;
class Response;
class Request;
class Cgi;
class Server;

class Location
{

public:
	Location();
	Location(const Location &src);
	~Location();

	Location &operator=(const Location &rhs);

	const std::string &getPath(void) const;
	const std::pair<int, std::string> &getReturn(void) const;
	const std::vector<std::string> &getMethods(void) const;
	const std::string &getRoot(void) const; 
	const std::vector<std::string> &getIndex(void) const;
	const bool &getAutoIndex(void) const;
	const std::string &getCgiExtension(void) const;
	const std::string &getCgiProgram(void) const;
	const std::string &getUploadStore(void) const;

	void setPath(const std::string &path);
	void setReturn(const std::vector<std::string> &token);
	void setMethods(const std::vector<std::string> &token);
	void setRoot(const std::vector<std::string> &token);
	void setIndex(const std::vector<std::string> &token);
	void setAutoIndex(const std::vector<std::string> &token);
	void setCgi(const std::vector<std::string> &token);
	void setCgiExtension(const std::string &extension);
	void setCgiProgram(const std::string &program);
	void setUploadStore(const std::vector<std::string> &token);

private:
	std::string _path;
	std::vector<std::string> _methods;
	std::string _root;
	std::vector<std::string> _index;
	bool _autoIndex;
	std::string _cgiExtension; 
	std::string _cgiProgram;  
	std::string _uploadStore;
	std::pair<int, std::string> _return;
};

#endif