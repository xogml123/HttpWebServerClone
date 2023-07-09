# COMPILATION
CC		= c++
CFLAGS 	= -Wall -Wextra -Werror -std=c++98 #-O2 #-fsanitize=address -g3
IFLAGS 	= -I./include


# DIRECTORIES
BUILD 			= build
SRC_DIR 		= srcs
OBJ_DIR 		= $(BUILD)/obj

DIRS			= $(OBJ_DIR) 
# $(addprefix $(OBJ_DIR)/, $(SUB_DIR))


# FILES
NAME			= webserv
SRC				= main.cpp \
				  Kqueue.cpp \
				  HttpMessage.cpp \
				  Location.cpp \
				  ParseFile.cpp \
				  Request.cpp \
				  Response.cpp \
				  Server.cpp \
				  Socket.cpp \
				  Utils.cpp \
				  Webserv.cpp \
				  Cgi.cpp

OBJ				= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

# MAKEFILE
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@


clean:
	@rm -rf $(BUILD)/*
	@mkdir $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re debug




