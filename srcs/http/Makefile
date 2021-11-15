SRC = 	test.cpp\
	middlewares/CheckSyntax.cpp\
	middlewares/BlockSelector.cpp\
	Request/Request.cpp\
	Request/requestParsing.cpp\
	Request/checkIncompleteRequest.cpp\
	Response/Response.cpp\
	../parsingConf/parsingConf.cpp\
	../parsingConf/serverBlock.cpp\
	../parsingConf/serverConfig.cpp\
	../parsingConf/serverLocation.cpp\
	../utils/utils.cpp\
	../utils/Log.cpp\
	../webserv/webserv.cpp\
	../server/Socket.cpp\
	../server/ActiveServer.cpp\
	../server/ActiveHTTP.cpp\
	../server/NIOSelector.cpp\
	../ipaddress/IPAddress.cpp\
	../ipaddress/INetAddress.cpp\

NAME = Webserv
HEADERS = -Iincludes 
CC = g++
CFLAGS = -g -Wall -Wextra -Werror -std=c++98
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
