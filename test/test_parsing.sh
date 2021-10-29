#!/usr/bin/env bash

touch fd1.txt
touch fd2.txt

FD1=fd1.txt
FD2=fd2.txt

g++ -g3 -D DEBUG -I ../includes -Wall -Werror -Wextra --std=c++98 ./test_parsing.cpp ../srcs/parsingConf/parsingConf.cpp ../srcs/parsingConf/serverBlock.cpp ../srcs/parsingConf/serverConfig.cpp ../srcs/parsingConf/serverLocation.cpp ../srcs/utils/utils.cpp ../srcs/webserv/webserv.cpp ../srcs/server/Socket.cpp  ../srcs/server/ActiveServer.cpp ../srcs/server/NIOSelector.cpp	../srcs/ipaddress/IPAddress.cpp ../srcs/ipaddress/INetAddress.cpp


./a.out $FD1 >> $FD2

if [ "$?" != "9" ]; then
	rm -f $FD1
	rm -f $FD2
	rm a.out
	exit 1
fi	
diff $FD1 $FD2
if [ "$(diff $FD1 $FD2 | wc -c)" != "0" ]; then
	rm -f $FD1
	rm -f $FD2
	rm a.out
	exit 1
fi

rm -f $FD1
rm -f $FD2
rm a.out
exit 0