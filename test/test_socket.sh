#!/usr/bin/env bash

g++ -D DEBUG -I../includes -Wall -Werror -Wextra --std=c++98 ../srcs/server/Socket.cpp ../srcs/server/ActiveSocket.cpp ../srcs/server/PassiveSocket.cpp ../srcs/ipaddress/INetAddress.cpp ./test_socket.cpp ../srcs/server/NIOSelector.cpp
PORT=8080
diff <(./a.out $PORT & sleep 1; echo "salut" | nc -w0 localhost $PORT) <(echo "SALUT")
