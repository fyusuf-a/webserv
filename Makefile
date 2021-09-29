SRC = 	main.cpp\
		srcs/config/config.cpp\
		srcs/server/server.cpp\
		srcs/server/serverConfig.cpp\
		srcs/utils/utils.cpp\
		srcs/webserv/webserv.cpp\
		srcs/server/TCPServer.cpp\
		srcs/ipaddress/INetAddress.cpp

NAME = Webserv
HEADERS = -Iincludes
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98
O_FILES = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(O_FILES)
	$(CC) $(CFLAGS) $(HEADERS) $(O_FILES) -o $(NAME)
	@echo "\033[33;32mCompilation...\t""\033[33;31mDONE 🙃"

debug: CFLAGS += -g3 -fsanitize=address
debug: CFLAGS += -D DEBUG
debug: all

clean :
	rm -f $(O_FILES)
	@echo "\033[33;36mDeleting - *.o..."

fclean : clean
	rm -f $(NAME)
	@echo "\033[33;36mDeleting - exec..."

re : fclean all

test : all
	cd test && ./test_tcpserver.sh

.cpp.o:
	${CC} ${CC_FLAGS} $(HEADERS) -c $< -o ${<:.cpp=.o}

.PHONY: all clean fclean re debug test
