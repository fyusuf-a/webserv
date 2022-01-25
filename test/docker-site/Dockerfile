FROM debian:buster-slim

ARG ROOT_DIR=/var/www/html/site

RUN apt-get update; \
		apt-get install -y php-fpm php7.3-mbstring php-cgi curl unzip git make g++ python3

RUN mkdir -p /var/www/html/site
COPY test/docker-site/site /var/www/html/site
COPY test/docker-site/srcs/site.conf /etc/webserv/site.conf
RUN sed -i 's+%ROOT_DIR%+'$ROOT_DIR'+g' /etc/webserv/site.conf

# webserv
COPY . /etc/webserv/
WORKDIR /etc/webserv
RUN make fclean && make debug -j4

EXPOSE 80

CMD /etc/webserv/Webserv /etc/webserv/site.conf
