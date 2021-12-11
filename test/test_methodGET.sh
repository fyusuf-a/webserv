#!/usr/bin/env bash

rm Response/my_*

g++ -g3 -D ERROR_FLAG -I../includes -Wall -Werror -Wextra --std=c++98 ../main.cpp\
	../srcs/parsingConf/parsingConf.cpp\
	../srcs/parsingConf/serverBlock.cpp\
	../srcs/parsingConf/serverConfig.cpp\
	../srcs/parsingConf/serverLocation.cpp\
	../srcs/utils/utils.cpp\
	../srcs/utils/Log.cpp\
	../srcs/webserv/webserv.cpp\
	../srcs/server/Socket.cpp\
	../srcs/server/ActiveServer.cpp\
	../srcs/server/ActiveHTTP.cpp\
	../srcs/server/NIOSelector.cpp\
	../srcs/ipaddress/IPAddress.cpp\
	../srcs/ipaddress/INetAddress.cpp\
	../srcs/http/middlewares/CheckSyntax.cpp\
	../srcs/http/middlewares/Error.cpp\
	../srcs/http/middlewares/BlockSelector.cpp\
	../srcs/http/middlewares/MethodChecker.cpp\
	../srcs/http/middlewares/MethodGET.cpp\
	../srcs/http/middlewares/MethodDELETE.cpp\
	../srcs/http/middlewares/MethodPOST.cpp\
	../srcs/http/middlewares/Sender.cpp\
	../srcs/http/middlewares/IndexSelector.cpp\
	../srcs/http/tasks/Task.cpp\
	../srcs/http/tasks/GETTask.cpp\
	../srcs/http/tasks/POSTTask.cpp\
	../srcs/http/middlewares/Middleware.cpp\
	../srcs/http/middlewares/MiddlewareChain.cpp\
	../srcs/http/middlewares/AbsolutePathConcatenator.cpp\
	../srcs/http/Request/Request.cpp\
	../srcs/http/Request/requestParsing.cpp\
	../srcs/http/Request/checkIncompleteRequest.cpp\
	../srcs/http/Response/Response.cpp\

./a.out ../conf/is_good.conf &
P1 = $!

sh ./requete.sh &
P2 = $!

wait $P1 $P2

if [ "$(diff ./Response/my_resp1 ./Response/resp1)" != "" ]; then
	echo "Error: response 1"
	rm a.out
	exit 1
fi

if [ "$(diff ./Response/my_resp2 ./Response/resp2)" != "" ]; then
	echo "Error: response 2"
	rm a.out
	exit 1
fi

if [ "$(diff ./Response/my_resp3 ./Response/resp3)" != "" ]; then
	echo "Error: response 3"
	rm a.out
	exit 1
fi

if [ "$(diff ./Response/my_resp4 ./Response/resp4)" != "" ]; then
	echo "Error: response 4"
	rm a.out
	exit 1
fi

if [ "$(diff ./Response/my_resp5 ./Response/resp5)" != "" ]; then
	echo "Error: response 5"
	rm a.out
	exit 1
fi

if [ "$(diff ./Response/my_resp6 ./Response/resp6)" != "" ]; then
	echo "Error: response 6"
	rm a.out
	exit 1
fi

if [ "$(diff ./Response/my_resp7 ./Response/resp7)" != "" ]; then
	echo "Error: response 7"
	rm a.out
	exit 1
fi

if [ "$(diff ./Response/my_resp8 ./Response/resp8)" != "" ]; then
	echo "Error: response 8"
	rm a.out
	exit 1
fi

if [ "$(diff ./Response/my_resp9 ./Response/resp9)" != "" ]; then
	echo "Error: response 9"
	rm a.out
	exit 1
fi

if [ "$(diff ./Response/my_resp10 ./Response/resp10)" != "" ]; then
	echo "Error: response 10"
	rm a.out
	exit 1
fi

if [ "$(diff ./Response/my_resp11 ./Response/resp11)" != "" ]; then
	echo "Error: response 11"
	rm a.out
	exit 1
fi

rm Response/my_*
rm a.out
exit 0
