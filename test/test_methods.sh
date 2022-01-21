#!/usr/bin/env bash
rm -f Response/GET/my_*
rm -f Response/DELETE/my_*
rm -f random*
rm -f ./test42/random*
rm -f ./Webserv
touch ./test42/delete_file
make -C .. fclean && make -C ..

mv ../Webserv ./
./Webserv test42/test_methods.conf &

sleep 5

bash Requete/requete.sh
kill $!

# \\ -------------- GET --------------- //
if [ "$(diff ./Response/GET/my_resp1 ./Response/GET/resp1)" != "" ]; then
	echo "Error: Response/GET 1"
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp2 ./Response/GET/resp2)" != "" ]; then
	echo "Error: Response/GET 2"
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp3 ./Response/GET/resp3)" != "" ]; then
	echo "Error: Response/GET 3"
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp4 ./Response/GET/resp4)" != "" ]; then
	diff ./Response/GET/my_resp4 ./Response/GET/resp4
	echo "Error: Response/GET 4"
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp5 ./Response/GET/resp5)" != "" ]; then
	echo "Error: Response/GET 5"
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp6 ./Response/GET/resp6)" != "" ]; then
	echo "Error: Response/GET 6"
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp7 ./Response/GET/resp7)" != "" ]; then
	echo "Error: Response/GET 7"
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp8 ./Response/GET/resp8)" != "" ]; then
	echo "Error: Response/GET 8"
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp9 ./Response/GET/resp9)" != "" ]; then
	echo "Error: Response/GET 9"
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp10 ./Response/GET/resp10)" != "" ]; then
	echo "Error: Response/GET 10"
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp11 ./Response/GET/resp11)" != "" ]; then
	echo "Error: Response/GET 11"
	exit 1
fi


# \\ -------------- POST --------------- //
if [ "$(diff random1.txt ./test42/random-output1.txt)" != "" ]; then
	echo "Error: POST 1"
	exit 1
fi
if [ "$(diff random2.txt ./test42/random-output2.txt)" != "" ]; then
	echo "Error: POST 2"
	exit 1
fi
if [ "$(diff random3.txt ./test42/random-output3.txt)" != "" ]; then
	echo "Error: POST 3"
	exit 1
fi

# \\ -------------- DELETE --------------- //
diff <(head -n 1 ./Response/DELETE/my_resp1) <(head -n 1 ./Response/DELETE/resp1)
if [ $? == "1" ]; then
	echo "Error: DELETE 1"
	exit 1
fi
diff <(head -n 1 ./Response/DELETE/my_resp2) <(head -n 1 ./Response/DELETE/resp2)
if [ $? == "1" ]; then
	echo "Error: DELETE 2"
	exit 1
fi


rm -f Response/GET/my_*
rm -f Response/DELETE/my_*
rm -f random*
rm -f ./test42/random* 

make fclean -C ..
rm Webserv

exit 0
