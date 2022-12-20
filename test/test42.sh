#!/usr/bin/env bash

if [ ! -f ubuntu_cgi_tester ]; then
	curl -Lo ubuntu_cgi_tester https://projects.intra.42.fr/uploads/document/document/5966/ubuntu_cgi_tester
	chmod +x ubuntu_tester
fi
if [ ! -f ubuntu_tester ]; then
	curl -Lo ubuntu_tester https://projects.intra.42.fr/uploads/document/document/5968/ubuntu_tester
	chmod +x ubuntu_tester
fi

make -C .. fclean
make -C .. test42
mv ../Webserv ./
./Webserv test42/test42.conf &

sleep 5

mkdir -p test42/put_test
mkdir -p test42/post_body
echo "youpi.bla's content" > test42/YoupiBanane/youpi.bla
echo '' | ./ubuntu_tester http://localhost:8001
echo "return value = $?"

kill $!
