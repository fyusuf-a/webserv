#!/usr/bin/env bash

rm -f test_methods/GET/my_*
rm -f test_methods/DELETE/my_*
rm -f random*
rm -f ./test42/random*
rm -f ./Webserv

touch ./test42/delete_file
make -C .. fclean && make -C .. debug -j4

../Webserv test_methods/test_methods.conf

sleep 2

# 1st argument : request number
# 2nd argument : path
function test_get() {
	curl -s localhost:8001$2 > test_methods/GET/my_resp$1
	if [ "$(diff ./test_methods/GET/my_resp$1 ./test_methods/GET/resp$1)" != "" ]; then
		echo "Error: GET $1"
		exit 1
	fi
}

# \\ -------------- GET --------------- //
test_get 1 "" GET
test_get 2 /directory GET
test_get 3 /directory/youpi.bad_extension GET
test_get 4 /directory/youpi.bla GET
test_get 5 /directory/oulalala GET
test_get 6 /directory/nop GET
test_get 7 /directory/nop/ GET
test_get 8 /directory/nop/other.pouic GET
test_get 9 /directory/nop/other.pouac GET
test_get 10 /directory/Yeah GET
test_get 11 /directory/Yeah/not_happy.bad_extension GET

# \\ -------------- DELETE --------------- //

# 1st argument : request number
# 2nd argument : path
# 3rd argument : expected status code
function test_delete() {
	RESP=$(curl -s -o /dev/null -w %{http_code} -X DELETE localhost:8001$2)
	if [ $RESP != $3 ]; then
		echo "dollar 2 = " $2
		echo -n "Error on DELETE request no $1: "
		echo expected $3, got $RESP
		exit 1
	fi
}
test_delete 1 /delete_file 204
test_delete 2 /delete_file 404

# \\ -------------- POST --------------- //

# 1st argument : request number
function test_post() {
	curl -v -X POST  --data-binary  @"random$1.txt" -H "Transfer-Encoding: chunked" http://localhost:8001/random-output$1.txt
	if [ "$(diff random$1.txt ./test42/random-output$1.txt)" != "" ]; then
		echo "Error: POST $1"
		exit 1
	fi
}

dd if=/dev/random of=random1.txt bs=1 count=158745
test_post 1

dd if=/dev/random of=random2.txt bs=1 count=10000000
test_post 2

yes this is a test | head -n 250000 > random3.txt
test_post 3

# \\ -------------- Cleaning up --------------- //

kill $!
make fclean -C ..

rm -f test_methods/GET/my_*
rm -f random*
rm -f ./test42/random* 

exit 0
