#include "Utils.hpp"

bool isNum(std::string str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (std::isdigit(str[i]) == 0)
			return false;
	}
	return true;
}

bool isIp(std::string str)
{
	size_t 		x;
	size_t 		n = 0;
	std::string	tmp = "";
	
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!std::isdigit(str[i]) && str[i] != '.')
			return false;
		if (std::isdigit(str[i]))
			tmp += str[i];
		if (str[i] == '.' || i == (str.size() - 1))
		{
			++n;
			std::stringstream(tmp) >> x;
			if (x > 255 || n > 4)
				return false;
			tmp = "";
		}
	}
	if (n != 4)
		return false;
	return true;
}

bool isDir(const std::string &path)
{
	struct stat fileInfo;

	stat(path.c_str(), &fileInfo);
	
	return (S_ISDIR(fileInfo.st_mode) != 0);
}

void	errorExit(const std::string &str)
{
	std::cerr << S_RED "Exit: " S_NONE << str << std::endl;
	exit(EXIT_FAILURE);
}

std::string	getExtension(const std::string& fileName)
{
	size_t pos = fileName.rfind(".");
	if (pos == std::string::npos)
		return std::string("");
	std::string	ext = fileName.substr(pos, fileName.size());
	return ext;
	
}

std::vector<std::string>	split_string(const std::string& s, const std::string& delim)
{
	std::string					tmp(s);
	std::vector<std::string>	v;
	std::string					line;
	size_t						pos = tmp.find(delim);

	if (delim[0] != '\0' && !s.empty())
	{
		while ((pos = tmp.find(delim)) != std::string::npos)
		{
			line = tmp.substr(0, pos);
			if (!tmp.empty())
				v.push_back(line);
			tmp.erase(0, pos + delim.length());
		}
	}
	if (!tmp.empty())
		v.push_back(tmp);
	return v;
}




std::string    ft_strcut(const std::string& str, char delimiter)
{
	size_t	pos = str.find(delimiter);

	if (pos == std::string::npos)
		return str;
	return str.substr(0, pos);
}


std::vector<std::string>	ft_vectorcut(const std::vector<std::string>& vect, char delimiter)
{
	std::vector<std::string>					newVect(vect);
	std::vector<std::string>::const_iterator	it;
	size_t										pos = 0;

	for(it = newVect.begin(); it != newVect.end(); ++it, ++pos)
	{
		if (*it != ft_strcut(*it, delimiter))
		{
			newVect[pos] = ft_strcut(*it, delimiter);
			if (!newVect[pos].empty())
				++it;
			break ;
		}
	}
	newVect.erase(it, newVect.end());
	return newVect;
}

std::string	vectorJoin(const std::vector<std::string> &vect, char sep)
{
    if (vect.empty())
        return std::string("");

    std::string	str = vect[0];

    for (size_t i = 1; i < vect.size(); ++i)
    {
        str += sep;
        str += vect[i];
    }
    return str;
}


bool	is_valid_path(const std::string& path)
{
	struct stat	stat_buf;

	return (0 == stat(path.c_str(), &stat_buf));
}


std::string	getFileContent(const std::string& file)
{
	std::ifstream	ifs(file, std::ios::in);
	std::string		content;
	std::string		gline;

	if (ifs.is_open())
	{
		do
		{
			std::getline(ifs, gline);
			content += gline;
			if (ifs.eof())
				break ;
			content += "\n";
		} while (true);
	}
	ifs.close();
	return content;
}

off_t	getFileLength(const std::string &file)
{
	struct stat	buf;

	if (isDir(file))
		return 0;
	if (SYSCALL_ERR != stat(file.c_str(), &buf))
		return buf.st_size;
	return SYSCALL_ERR;
}

void	handleSignals(int sig)
{
	std::cout << std::endl << S_RED "[Quit]" S_NONE << std::endl;
	if (SIGINT == sig)
		exit(EXIT_SUCCESS);
}

void	warnMsg(const std::string &str)
{
	std::cerr << S_YELLOW "Warning: " S_NONE << str << std::endl;
}

void	updateMsg(const std::string &str)
{
	std::cout << S_PURPLE "Updating: " S_NONE << str << std::endl;
}

