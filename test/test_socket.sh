#!/usr/bin/env bash

g++ -I../includes -Wall -Werror -Wextra --std=c++98 ../srcs/server/Socket.cpp ../srcs/server/ActiveSocket.cpp ../srcs/server/PassiveSocket.cpp ../srcs/ipaddress/INetAddress.cpp ./test_socket.cpp
PORT=8080
diff <(./a.out $PORT & sleep 1; echo "salut" | nc -w0 localhost $PORT) <(echo "SALUT")
