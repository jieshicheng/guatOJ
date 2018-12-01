# docker compiler and run env
# for judge end.
# if you living in china, you should using vpn or anything else to across the wall
#  otherwise may not be able to build this images.

FROM ubuntu:latest
MAINTAINER linkcheng "951497836@qq.com"
ENV REFRESHED_AT 2018-11-2

RUN apt-get -y update
# convienient to debug
RUN apt-get -y install vim 

# cmake
RUN apt-get -y update 
RUN apt-get -y install make

# must greater than 7.2 to complier cinatra
RUN apt-get -y install gcc 
RUN apt-get -y install g++ 

RUN apt-get -y install git

# boost and uuid. complier environment for cinatra
RUN apt-cache search boost
RUN apt-get -y install libboost-all-dev

RUN apt-get -y install uuid-dev

# locate command for debug
RUN apt-get -y install mlocate
RUN updatedb

# download guatOJ 
WORKDIR /root/guatOJ/
RUN git clone https://github.com/jieshicheng/guatOJ.git

EXPOSE 80
