# docker compiler and run env
# for judge end.

FROM ubuntu:latest
MAINTAINER linkcheng "951497836@qq.com"
ENV REFRESHED_AT 2018-11-2

RUN apt-get -y update
# convienient to debug
RUN apt-get -y install vim 

# cmake
RUN apt-get -y install cmake

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

# download thirth part framework
# cinatra -----http server framework
WORKDIR /root/guatOJ/
RUN git clone https://github.com/qicosmos/cinatra.git

# g++ -o server cjstest.cpp -std=c++17 -L/usr/lib/x86_64-linux-gnu -lboost_filesystem -lboost_system -lpthread -luuid -lstdc++fs
