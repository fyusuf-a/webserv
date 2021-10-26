#!/usr/bin/env bash

g++ -g -D DEBUG -I../includes -Wall -Werror -Wextra --std=c++98 ../srcs/ipaddress/IPAddress.cpp ../srcs/server/Socket.cpp ../srcs/ipaddress/INetAddress.cpp ./test_socket.cpp ../srcs/server/NIOSelector.cpp
PORT=8080
diff <(valgrind --show-leak-kinds=all --leak-check=full --error-exitcode=1 ./a.out $PORT & sleep 4; echo "salut" | nc -w0 localhost $PORT) <(echo "SALUT")
wait $!
