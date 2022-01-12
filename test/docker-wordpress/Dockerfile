FROM debian:buster-slim

ARG ROOT_DIR=/var/www/html/wordpress
ARG AUTOINDEX=on

RUN apt-get update; \
		apt-get install -y php-fpm mariadb-server php7.3-mysql php7.3-mbstring php-cgi curl unzip git make g++

# mariadb
COPY srcs/create.sql /
RUN service mysql start && \
		mysql < create.sql && \
		rm create.sql

# webserv
RUN git clone https://github.com/fyusuf-a/webserv /etc/webserv; \
	make -C /etc/webserv debug

# wordpress
RUN mkdir -p /var/www/html && \
	curl -L https://wordpress.org/latest.tar.gz | tar -xz -C /var/www/html
COPY srcs/wordpress.conf /etc/webserv/wordpress.conf
RUN sed -i 's+%ROOT_DIR%+'$ROOT_DIR'+g' /etc/webserv/wordpress.conf ; \
		sed -i 's/%AUTOINDEX%/'$AUTOINDEX'/g' /etc/webserv/wordpress.conf ; \
		rm /var/www/html/wordpress/wp-config-sample.php
COPY srcs/wp-config.php /var/www/html/wordpress/

EXPOSE 80

CMD service mysql start &&\
	/etc/webserv/Webserv /etc/webserv/wordpress.conf
