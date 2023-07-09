#include "Location.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Location::Location() : _path(""), _root(""), _autoIndex(false), _cgiExtension(""), _cgiProgram(""), _uploadStore("")
{
	this->_methods.push_back("GET");
	this->_index.push_back("");
}

Location::Location(const Location &src)
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Location::~Location()
{
	this->_methods.clear();
	this->_index.clear();

	std::vector<std::string>().swap(_methods);
	std::vector<std::string>().swap(_index);
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Location &Location::operator=(Location const &rhs)
{
	if (this != &rhs)
	{
		this->_path = rhs._path;
		this->_methods = rhs._methods;
		this->_root = rhs._root;
		this->_index = rhs._index;
		this->_autoIndex = rhs._autoIndex;
		this->_cgiExtension = rhs._cgiExtension;
		this->_cgiProgram = rhs._cgiProgram;
		this->_uploadStore = rhs._uploadStore;
	}

	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::string &Location::getPath(void) const
{
	return _path;
}

const std::vector<std::string> &Location::getMethods(void) const
{
	return _methods;
}

const std::string &Location::getRoot(void) const
{
	return _root;
}

const std::vector<std::string> &Location::getIndex(void) const
{
	return _index;
}
const bool &Location::getAutoIndex(void) const
{
	return _autoIndex;
}
const std::string &Location::getCgiExtension(void) const
{
	return _cgiExtension;
}
const std::string &Location::getCgiProgram(void) const
{
	return _cgiProgram;
}

const std::string &Location::getUploadStore(void) const
{
	return _uploadStore;
}

const std::pair<int, std::string> &Location::getReturn(void) const
{
	return this->_return;
}

void Location::setPath(const std::string &path)
{
	this->_path = path;
}



void Location::setMethods(const std::vector<std::string> &token)
{
	std::string mlist[] = {"GET", "POST", "DELETE"};
	size_t i;

	for (std::vector<std::string>::const_iterator it = token.begin() + 1; it != token.end(); ++it)
	{
		if (!std::find(mlist, mlist + 2, *it))
		{
			std::cout << "setMethods\n";
			throw ParseFile::ParsingError();
		}

		for (i = 0; i < mlist->size(); ++i)
			if (*it == mlist[i])
			{
				if (std::find(this->getMethods().begin(), this->getMethods().end(), mlist[i]) == this->getMethods().end())
					this->_methods.push_back(mlist[i]);
			}
	}
}

void Location::setReturn(const std::vector<std::string> &token)
{
	if (token.size() != 3 || !isNum(token[1]))
	{
		std::cout << "setReturn\n";
		throw ParseFile::ParsingError();
	}

	std::stringstream(token[1]) >> this->_return.first;

	if (this->_return.first < 300 || (this->_return.first > 304 && this->_return.first < 307))
	{
		std::cout << "setReturn 2\n";
		throw ParseFile::ParsingError();
	}

	this->_return.second = token[2];
}

void Location::setRoot(const std::vector<std::string> &token)
{
	if (token.size() != 2)
	{
		std::cout << "setRoot\n";
		throw ParseFile::ParsingError();
	}

	if (token[1][0] != '/')
		this->_root = '/' + token[1];
	else
		this->_root = token[1];
}

void Location::setIndex(const std::vector<std::string> &token)
{
	if (token.size() < 2)
	{
		std::cout << "setIndex\n";
		throw ParseFile::ParsingError();
	}

	this->_index.assign(token.begin() + 1, token.end());
}

void Location::setAutoIndex(const std::vector<std::string> &token)
{
	if (token.size() != 2)
	{
		std::cout << "setAutoIndex\n";
		throw ParseFile::ParsingError();
	}
	if (token[1] == "on")
		this->_autoIndex = AUTOINDEX_ON;
	else if (token[1] != "off")
	{
		std::cout << "setAutoIndex 2\n";
		throw ParseFile::ParsingError();
	}
}

void Location::setCgi(const std::vector<std::string> &token)
{
	if (token.size() != 3)
	{
		std::cout << "setCgi\n";
		throw ParseFile::ParsingError();
	}

	this->setCgiExtension(token[1]);
	this->setCgiProgram(token[2]);
}

void Location::setCgiExtension(const std::string &extension)
{
	this->_cgiExtension = extension;
}

void Location::setCgiProgram(const std::string &program)
{
	this->_cgiProgram = program;
}

void Location::setUploadStore(const std::vector<std::string> &token)
{
	if (token.size() != 2 || !isDir(ROOT_PATH + token[1]))
	{
			std::cout << token[1];
			std::cout << " 2\n";
	
		std::cout << "setUploadStore\n";
		throw ParseFile::ParsingError();
	}

	this->_uploadStore = token[1];
	if (token[1].back() != '/')
		this->_uploadStore += "/";
}

/* ************************************************************************** */