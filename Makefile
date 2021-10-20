SRC = 	main.cpp\
	srcs/parsingConf/parsingConf.cpp\
	srcs/parsingConf/serverBlock.cpp\
	srcs/parsingConf/serverConfig.cpp\
	srcs/parsingConf/serverLocation.cpp\
	srcs/utils/utils.cpp\
	srcs/webserv/webserv.cpp\
	srcs/server/Socket.cpp\
	srcs/server/ActiveServer.cpp\
	srcs/server/NIOSelector.cpp\
	srcs/ipaddress/IPAddress.cpp\
	srcs/ipaddress/INetAddress.cpp

NAME = Webserv
HEADERS = -Iincludes 
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98
O_FILES = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(O_FILES)
	$(CC) $(CFLAGS) $(HEADERS) $(O_FILES) -o $(NAME)
	@echo "\033[33;32mCompilation...\t""\033[33;31mDONE 🙃\033[0m"

debug: CFLAGS += -g3 -fsanitize=address
debug: CFLAGS += -D DEBUG
debug: all

clean :
	rm -f $(O_FILES)
	@echo "\033[33;36mDeleting - *.o...\033[0m"

fclean : clean
	rm -f $(NAME)
	@echo "\033[33;36mDeleting - exec...\033[0m"

re : fclean all

test : all
	cd test && ./test_socket.sh
	cd test && ./test_nioselector.sh

.cpp.o:
	${CC} ${CFLAGS} $(HEADERS) -c $< -o ${<:.cpp=.o}

.PHONY: all clean fclean re debug test
