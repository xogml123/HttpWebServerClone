#ifndef KQUEUE_HPP
# define KQUEUE_HPP

# include "Defs.hpp"
# include "Socket.hpp"
# include "Utils.hpp"


class Kqueue {
	public:
		
		typedef std::map<const int, Socket>                    conn_type;
		typedef std::map<const int, Request*>                  req_type;

	public:
		explicit Kqueue(Socket *, int const &);
		~Kqueue(void);

		void	startKqueue(void);

	private:
		Kqueue(void);

		void	_serverLoop(void);
		
		Socket *	_checkServ(int const &, std::map<const int, Socket> &) const;

		bool	_checkClient(int const &) const;

		void	_updateEvt(int ident, short filter, u_short flags, u_int fflags, int data, void *udata, std::string debugMsg);

		bool	_clientConnect(int const &, std::map<const int, Socket> &);

		void	_clientDisconnect(int const &, std::map<const int, Socket> &);

		void	_handleRequest(struct kevent const &, Socket &);

	private:
		Socket				*_serverSocks;
		int					_serverSize;
		int					_kqueueFd;

		static const int	_nEvents = 1024;
		struct kevent		_evlist[_nEvents];

		conn_type			_connMap;
		req_type			_reqMap;

};


#endif
