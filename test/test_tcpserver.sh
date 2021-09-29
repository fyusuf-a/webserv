#!/usr/bin/env bash

g++ -I../includes -Wall -Werror -Wextra --std=c++98 ../srcs/server/TCPServer.cpp ../srcs/ipaddress/INetAddress.cpp ./tcpserver/test_tcpserver.cpp
PORT=8080
diff <(./a.out $PORT & sleep 1; echo "salut" | nc -w0 localhost $PORT) <(echo "SALUT")
