#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "Defs.hpp"
# include "Kqueue.hpp"
# include "ParseFile.hpp"
# include "Utils.hpp"


class cgi;
class Socket;
class Kqueue;

class Webserv
{
	public:
		Webserv(ParseFile& parseFile);
		~Webserv();
	
	private:
		Webserv(const Webserv &);
		Webserv&				operator=(const Webserv &);
	
	public:
		void					parse(const std::string &);
		size_t					serverSize(void) const;
		const Server&			getServer(int) const;
		void					createServers(void);

	private:
		size_t					countSocket() const;
		std::vector<Server *>	selectServers(size_t& index);

	public:
		class ParsingError : public std::exception
		{
			public:
				virtual const char*	what() const throw();
		};
		
	private:
        
		std::vector<Server *> &	_servers;
		Socket				*_socks;
	
};


#endif
