#!/usr/bin/env bash

g++ -D DEBUG -I../includes -Wall -Werror -Wextra --std=c++98 ../srcs/server/Socket.cpp ../srcs/ipaddress/INetAddress.cpp ./test_nioselector.cpp ../srcs/server/NIOSelector.cpp \
	../srcs/server/ActiveServer.cpp
PORT1=8080
PORT2=8081
./a.out & sleep 1
PID=$!
echo -n "s" | nc -w1 localhost $PORT1 > my_test.txt ; echo -n "N" | nc -w1 localhost $PORT2 >> my_test.txt
if [ "$(cat my_test.txt | wc -c)" -ne "2" ]; then
	exit 1
fi
if [ ! $(cat my_test.txt | grep n) ]; then
	exit 1
fi
if [ ! $(cat my_test.txt | grep S) ]; then
	exit 1
fi
kill $PID
rm my_test.txt
