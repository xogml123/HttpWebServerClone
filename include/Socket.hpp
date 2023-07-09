#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "Defs.hpp"
# include "Server.hpp"
# include "Response.hpp"



class Socket
{
	public:
		typedef std::vector< std::string >		vector_type;
		typedef std::pair< int, std::string >	pair_type;
		typedef std::map<const int, Response*>	resp_type;

	public:

		explicit Socket(void);
		explicit Socket(const std::vector<Server *>);
		Socket(const Socket &);
		~Socket();
		Socket&			operator=(const Socket &);

	public:
		short			getPort(void) const;
		int				getServerFd(void) const;
		const Server*	getServer(void) const;
		sockaddr_in		getAddr(void) const;
		size_t			getAddrLen(void) const;
		Response		*getCurrResponse(int const) const;

		const Server*	selectServer(const std::string &) const;

		void			startSocket(void);
		
		int				readHttpRequest(Request *, struct kevent currEvt);
		int				resolveHttpRequest(Request *);
		int				sendHttpResponse(Request *, int);

		void			setNonBlock(int & fd);
		int				socketAccept(void);


	private:
		void			bindStep(const int &, const sockaddr_in &);
		void			listenStep(const int &);
		
		void			setHeaderData(const std::string &);
		std::string		constructPath(void);

		size_t			requestLen(std::string const &);
		
	private:
		std::vector<Server *>	_server_blocks;
		short					_port;
		int						_serverFd;
		sockaddr_in				_addr;
		size_t					_addrLen;
	
		int						_sendStatus;
		resp_type				_respMap;
		Response				*_currResponse;

};


#endif
