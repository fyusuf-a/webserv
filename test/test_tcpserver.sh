#!/usr/bin/env bash

clang++ -I../includes -Wall -Werror -Wextra --std=c++98 ../srcs/server/TCPServer.cpp ../srcs/ipaddress/INetAddress.cpp ./tcpserver/test_tcpserver.cpp
PORT=8080
diff <(./a.out $PORT & sleep 1; echo "salut" | nc localhost $PORT) <(echo "SALUT")
