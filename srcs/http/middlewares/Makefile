SRC = 	main.cpp\
	../../parsingConf/parsingConf.cpp\
	../../parsingConf/serverBlock.cpp\
	../../parsingConf/serverConfig.cpp\
	../../parsingConf/serverLocation.cpp\
	../../utils/utils.cpp\
	../../utils/Log.cpp\
	../../webserv/webserv.cpp\
	../../server/Socket.cpp\
	../../server/ActiveServer.cpp\
	../../server/ActiveHTTP.cpp\
	../../server/NIOSelector.cpp\
	../../ipaddress/IPAddress.cpp\
	../../ipaddress/INetAddress.cpp\
	CheckSyntax.cpp\
	BlockSelector.cpp\
	MethodChecker.cpp\
	MethodGET.cpp\
	MethodDELETE.cpp\
	MethodPOST.cpp\
	Sender.cpp\
	Middleware.cpp\
	MiddlewareChain.cpp\
	AbsolutePathConcatenator.cpp\
	IndexSelector.cpp\
	../Request/Request.cpp\
	../Request/requestParsing.cpp\
	../Request/checkIncompleteRequest.cpp\
	../Response/Response.cpp

NAME = test_middlewares
HEADERS = -I../../../includes 
CC = g++
CFLAGS = -g -Wall -Wextra -Werror -std=c++98
O_FILES = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(O_FILES)
	$(CC) $(CFLAGS) $(HEADERS) $(O_FILES) -o $(NAME)
	@echo "\033[33;32mCompilation...\t""\033[33;31mDONE 🙃\033[0m"

apc: CFLAGS += -D APC_FLAG
apc: all
block_selector: CFLAGS += -D BS_FLAG
block_selector: all
check_syntax: CFLAGS += -D CS_FLAG
check_syntax: all
index_selector: CFLAGS += -D IS_FLAG
index_selector: all
method_checker: CFLAGS += -D MC_FLAG
method_checker: all
method_delete: CFLAGS += -D MD_FLAG
method_delete: all
method_get: CFLAGS += -D MG_FLAG
method_get: all
method_post: CFLAGS += -D MP_FLAG
method_post: all

test: CFLAGS += -D APC_FLAG -D BS_FLAG -D CS_FLAG -D IS_FLAG -D MC_FLAG -D MD_FLAG -D MG_FLAG -D MP_FLAG
test: all

clean :
	rm -f $(O_FILES)
	@echo "\033[33;36mDeleting - *.o...\033[0m"

fclean : clean
	rm -f $(NAME)
	@echo "\033[33;36mDeleting - exec...\033[0m"

re : fclean all

.cpp.o:
	${CC} ${CFLAGS} $(HEADERS) -c $< -o ${<:.cpp=.o}

.PHONY: all clean fclean re debug test
