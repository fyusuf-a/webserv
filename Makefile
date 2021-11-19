SRC = 	main.cpp\
	srcs/parsingConf/parsingConf.cpp\
	srcs/parsingConf/serverBlock.cpp\
	srcs/parsingConf/serverConfig.cpp\
	srcs/parsingConf/serverLocation.cpp\
	srcs/utils/utils.cpp\
	srcs/utils/Log.cpp\
	srcs/webserv/webserv.cpp\
	srcs/server/Socket.cpp\
	srcs/server/ActiveServer.cpp\
	srcs/server/ActiveHTTP.cpp\
	srcs/server/NIOSelector.cpp\
	srcs/ipaddress/IPAddress.cpp\
	srcs/ipaddress/INetAddress.cpp\
	srcs/http/middlewares/CheckSyntax.cpp\
	srcs/http/middlewares/BlockSelector.cpp\
	srcs/http/middlewares/MethodChecker.cpp\
	srcs/http/middlewares/MethodGET.cpp\
	srcs/http/middlewares/Sender.cpp\
	srcs/http/middlewares/Middleware.cpp\
	srcs/http/middlewares/MiddlewareChain.cpp\
	srcs/http/middlewares/AbsolutePathConcatenator.cpp\
	srcs/http/Request/Request.cpp\
	srcs/http/Request/requestParsing.cpp\
	srcs/http/Request/checkIncompleteRequest.cpp\
	srcs/http/Response/Response.cpp

NAME = Webserv
HEADERS = -Iincludes 
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98
O_FILES = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(O_FILES)
	$(CC) $(CFLAGS) $(HEADERS) $(O_FILES) -o $(NAME)
	@echo "\033[33;32mCompilation...\t""\033[33;31mDONE 🙃\033[0m"

debug: CFLAGS += -g3
debug: CFLAGS += -D DEBUG_FLAG
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
	cd test && ./test_multiple_addresses_bind.sh
	cd test && ./test_parsing.sh

.cpp.o:
	${CC} ${CFLAGS} $(HEADERS) -c $< -o ${<:.cpp=.o}

.PHONY: all clean fclean re debug test
