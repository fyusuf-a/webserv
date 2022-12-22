#!/usr/bin/env bash

g++ -g -D DEBUG_FLAG -I../includes -Wall -Werror -Wextra --std=c++98 ../srcs/utils/Log.cpp ../srcs/ipaddress/IPAddress.cpp ../srcs/server/Socket.cpp ../srcs/ipaddress/INetAddress.cpp ./test_socket.cpp ../srcs/server/NIOSelector.cpp ../srcs/utils/utils.cpp
PORT=8080
diff <(valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./a.out $PORT & sleep 4; echo "salut" | nc -w0 localhost $PORT) <(echo "SALUT")
wait $!
