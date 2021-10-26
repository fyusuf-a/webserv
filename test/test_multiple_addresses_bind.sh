#!/usr/bin/env bash

make -C ..
../Webserv tests_conf/multiple_addresses_and_ports.conf &
sleep 2 && ps -p $!
RET=$?
kill -9 $!
exit $RET
