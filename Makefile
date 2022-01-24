SRC = 	main.cpp\
	srcs/parsingConf/parsingConf.cpp\
	srcs/parsingConf/serverBlock.cpp\
	srcs/parsingConf/serverConfig.cpp\
	srcs/parsingConf/serverLocation.cpp\
	srcs/utils/utils.cpp\
	srcs/utils/Log.cpp\
	srcs/utils/TransferEncoding.cpp\
	srcs/utils/HeaderMap.cpp\
	srcs/webserv/webserv.cpp\
	srcs/server/Socket.cpp\
	srcs/server/ActiveServer.cpp\
	srcs/server/ActiveHTTP.cpp\
	srcs/server/NIOSelector.cpp\
	srcs/ipaddress/IPAddress.cpp\
	srcs/ipaddress/INetAddress.cpp\
	srcs/http/middlewares/CheckSyntax.cpp\
	srcs/http/middlewares/Error.cpp\
	srcs/http/middlewares/MethodChecker.cpp\
	srcs/http/middlewares/MethodGET.cpp\
	srcs/http/middlewares/MethodDELETE.cpp\
	srcs/http/middlewares/MethodPOST.cpp\
	srcs/http/middlewares/Extract_query_and_extension.cpp\
	srcs/http/middlewares/PathChopper.cpp\
	srcs/http/middlewares/Sender.cpp\
	srcs/http/middlewares/IndexSelector.cpp\
	srcs/http/tasks/Task.cpp\
	srcs/http/tasks/GETTask.cpp\
	srcs/http/tasks/POSTTask.cpp\
	srcs/http/tasks/CGIOutTask.cpp\
	srcs/http/middlewares/Middleware.cpp\
	srcs/http/middlewares/MiddlewareChain.cpp\
	srcs/http/middlewares/AbsolutePathConcatenator.cpp\
	srcs/http/middlewares/CGIRunner.cpp\
	srcs/http/Request/Request.cpp\
	srcs/http/Request/requestParsing.cpp\
	srcs/http/Request/BlockSelector.cpp\
	srcs/http/Response/Response.cpp\

NAME = Webserv
HEADERS = -I includes 
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g3
O_FILES = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(O_FILES)
	$(CC) $(CFLAGS) $(HEADERS) $(O_FILES) -o $(NAME)
	@echo "\033[33;32mCompilation...\t""\033[33;31mDONE 🙃\033[0m"

debug: CFLAGS +=
debug: CFLAGS += -D DEBUG_FLAG
debug: all

test42: CFLAGS += -D TEST42 -D DEBUG_FLAG
test42: all

site:
	docker rm -f web_server && \
	docker build -t webserv -f test/docker-site/Dockerfile . && \
	docker run --name web_server -p 80:80 -d webserv

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
	cd test && ./test_methods.sh

.cpp.o:
	${CC} ${CFLAGS} $(HEADERS) -c $< -o ${<:.cpp=.o}

.PHONY: all clean fclean re debug test
