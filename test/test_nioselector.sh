#!/usr/bin/env bash

g++ -g3 -D DEBUG -I../includes -Wall -Werror -Wextra --std=c++98 ../srcs/server/Socket.cpp ../srcs/ipaddress/INetAddress.cpp ./test_nioselector.cpp ../srcs/server/NIOSelector.cpp ../srcs/ipaddress/IPAddress.cpp\
	../srcs/server/ActiveServer.cpp
PORT1=8080
PORT2=8081
valgrind --show-leak-kinds=all --leak-check=no --error-exitcode=1 ./a.out & sleep 4
echo -n "s" | nc -w1 localhost $PORT1 > my_test.txt ; echo -n "N" | nc -w1 localhost $PORT2 >> my_test.txt
kill $!
if [ "$(cat my_test.txt | wc -c)" -ne "2" ]; then
	rm my_test.txt
	exit 1
fi
if [ ! $(cat my_test.txt | grep n) ]; then
	rm my_test.txt
	exit 1
fi
if [ ! $(cat my_test.txt | grep S) ]; then
	rm my_test.txt
	exit 1
fi
rm my_test.txt
exit 0
