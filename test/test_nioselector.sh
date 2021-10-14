#!/usr/bin/env sh

g++ -D DEBUG -I../includes -Wall -Werror -Wextra --std=c++98 ../srcs/server/Socket.cpp ../srcs/ipaddress/INetAddress.cpp ./test_nioselector.cpp ../srcs/server/NIOSelector.cpp \
	../srcs/server/ActiveServer.cpp
PORT1=8080
PORT2=8081
./a.out & sleep 1
echo "s" | nc -w0 localhost $PORT1 >> my_test.txt ; echo "N" | nc -w0 localhost $PORT2 >> my_test.txt

//rm my_test.txt
