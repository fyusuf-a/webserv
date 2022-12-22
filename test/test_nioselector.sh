#!/usr/bin/env bash

g++ -g3 -D DEBUG_FLAG -I../includes -Wall -Werror -Wextra --std=c++98 ../srcs/utils/Log.cpp ../srcs/server/Socket.cpp ../srcs/ipaddress/INetAddress.cpp ./test_nioselector.cpp ../srcs/server/NIOSelector.cpp ../srcs/ipaddress/IPAddress.cpp ../srcs/server/ActiveServer.cpp ../srcs/utils/utils.cpp
PORT1=8080
PORT2=8081

valgrind --leak-check=full --show-leak-kinds=all ./a.out 2>valgrind.log &
sleep 1
echo -n "s" | nc -w1 localhost $PORT1 > my_test.txt ; echo -n "N" | nc -w1 localhost $PORT2 >> my_test.txt
if  pgrep -f valgrind > /dev/null; then
	echo Program exists
	kill $!
else
	echo Program does not exist any more
	exit 1
fi
if cat valgrind.log | grep Invalid ; then
	echo "valgrind.log"
	cat valgrind.log
	rm -f valgrind.log
	exit 1
fi
rm -f valgrind.log
if [ "$(cat my_test.txt | wc -c)" -ne "2" ]; then
	echo Output does not contain 2 letters
	rm my_test.txt
	exit 1
fi
if [ ! $(cat my_test.txt | grep n) ]; then
	echo Output does not contain N
	rm my_test.txt
	exit 1
fi
if [ ! $(cat my_test.txt | grep S) ]; then
	echo Output does not contain s
	rm my_test.txt
	exit 1
fi
rm -f my_test.txt
exit 0
