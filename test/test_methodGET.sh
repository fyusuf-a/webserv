#!/usr/bin/env bash

make -C ..

sed "s|%ROOT%|$PWD|g" 42_tester_stub.conf > 42_tester.conf

../Webserv 42_tester.conf & sh Requete/requete.sh
kill $!

# \\ -------------- GET--------------- //
if [ "$(diff ./Response/GET/my_resp1 ./Response/GET/resp1)" != "" ]; then
	echo "Error: Response/GET 1"
	rm a.out
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp2 ./Response/GET/resp2)" != "" ]; then
	echo "Error: Response/GET 2"
	rm a.out
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp3 ./Response/GET/resp3)" != "" ]; then
	echo "Error: Response/GET 3"
	rm a.out
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp4 ./Response/GET/resp4)" != "" ]; then
	echo "Error: Response/GET 4"
	rm a.out
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp5 ./Response/GET/resp5)" != "" ]; then
	echo "Error: Response/GET 5"
	rm a.out
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp6 ./Response/GET/resp6)" != "" ]; then
	echo "Error: Response/GET 6"
	rm a.out
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp7 ./Response/GET/resp7)" != "" ]; then
	echo "Error: Response/GET 7"
	rm a.out
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp8 ./Response/GET/resp8)" != "" ]; then
	echo "Error: Response/GET 8"
	rm a.out
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp9 ./Response/GET/resp9)" != "" ]; then
	echo "Error: Response/GET 9"
	rm a.out
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp10 ./Response/GET/resp10)" != "" ]; then
	echo "Error: Response/GET 10"
	rm a.out
	exit 1
fi
if [ "$(diff ./Response/GET/my_resp11 ./Response/GET/resp11)" != "" ]; then
	echo "Error: Response/GET 11"
	rm a.out
	exit 1
fi


# \\ -------------- POST --------------- //
# if [ "$(diff ./Response/POST/my_resp1 ./Response/POST/resp1)" != "" ]; then
# 	echo "Error: Response/POST 1"
# 	rm a.out
# 	exit 1
# fi
# if [ "$(diff ./Response/POST/my_resp2 ./Response/POST/resp2)" != "" ]; then
# 	echo "Error: Response/POST 2"
# 	rm a.out
# 	exit 1
# fi
# if [ "$(diff ./Response/POST/my_resp3 ./Response/POST/resp3)" != "" ]; then
# 	echo "Error: Response/POST 3"
# 	rm a.out
# 	exit 1
# fi
# if [ "$(diff ./Response/POST/my_resp4 ./Response/POST/resp4)" != "" ]; then
# 	echo "Error: Response/POST 4"
# 	rm a.out
# 	exit 1
# fi
# if [ "$(diff ./Response/POST/my_resp5 ./Response/POST/resp5)" != "" ]; then
# 	echo "Error: Response/POST 5"
# 	rm a.out
# 	exit 1
# fi
# if [ "$(diff ./Response/POST/my_resp6 ./Response/POST/resp6)" != "" ]; then
# 	echo "Error: Response/POST 6"
# 	rm a.out
# 	exit 1
# fi
# if [ "$(diff ./Response/POST/my_resp7 ./Response/POST/resp7)" != "" ]; then
# 	echo "Error: Response/POST 7"
# 	rm a.out
# 	exit 1
# fi
# if [ "$(diff ./Response/POST/my_resp8 ./Response/POST/resp8)" != "" ]; then
# 	echo "Error: Response/POST 8"
# 	rm a.out
# 	exit 1
# fi

#rm -f Response/GET/my_*
rm -f a.out
exit 0
