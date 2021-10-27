#!/usr/bin/env bash

make -C ..
../Webserv tests_conf/multiple_addresses_and_ports.conf > /dev/null &
sleep 2 && pgrep "Webserv" > /dev/null
RET=$?
kill -9 $!
exit $RET
