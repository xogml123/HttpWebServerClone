#ifndef DEFS_HPP
# define DEFS_HPP

# define S_NONE    "\e[0m"
# define S_RED     "\e[1;31m"
# define S_GREEN   "\e[1;32m"
# define S_YELLOW  "\e[1;33m"
# define S_BLUE    "\e[1;34m"
# define S_PURPLE  "\e[1;35m"
# define S_CYAN    "\e[1;36m"



# define ROOT_PATH              "./www"
# define CONFIG_DEFAULT_PATH    "./config_files"
# define CONFIG_FILETYPE        ".conf"
# define DEFAULT_CONFIG_FILE    CONFIG_DEFAULT_PATH "/default" CONFIG_FILETYPE

# define HTTP_PROTOCOL_VERSION  "HTTP/1.1"

# define NEW_LINE               "\r\n"
# define DELIMITER              "\r\n\r\n"


# define SYSCALL_ERR    (-1)

#ifndef SOMAXCONN
# define SOMAXCONN      128
#endif

# define AUTOINDEX_OFF  false
# define AUTOINDEX_ON   true

# define FD_IN          0
# define FD_OUT         1

# define BUFFER_SIZE    4096



enum	e_read
{
	READ_OK,
	READ_FAIL,
	READ_DISCONNECT
};

enum	e_resolve
{
	RESOLVE_OK,
	RESOLVE_FAIL,
	RESOLVE_EMPTY
};

enum	e_send
{
	SEND_OK,
	SEND_CGI_FAIL,
	SEND_FAIL,
	WAIT_SEND,
	CONTINU_SEND,
	NOFOUND_SEND
};

enum	e_cgi
{
	CGI_INIT_STATUS,
	CGI_EXECUTE_STATUS,
	CGI_READ_STATUS,
	CGI_DONE_STATUS
};

# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/types.h>
# include <sys/event.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/cdefs.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <signal.h>

# include <string>
# include <cstring>
# include <cstdio>
# include <cstdlib>
# include <cctype>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <exception>

# include <map>
# include <vector>
# include <list>
# include <algorithm>

# include "Utils.hpp"

#endif
