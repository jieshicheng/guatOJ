# docker compiler and run env
# for judge end.
# if you living in china, you should using vpn or anything else to across the wall
#  otherwise may not be able to build this images.

FROM ubuntu:18.10
MAINTAINER linkcheng "951497836@qq.com"
ENV REFRESHED_AT 2018-11-2

# install
# make; vim; gcc; g++; git
# gcc; g++ requirement up to 7.2
RUN apt-get update && apt-get -y install vim make gcc g++ git 

# boost and uuid. complier environment for cinatra
RUN apt-get clean && cd /var/lib/apt && mv lists lists.old && mkdir -p lists/partial && \
apt-get clean && apt-get update && \
apt-cache search boost && apt-get -y install libboost-all-dev uuid-dev

# locate command for debug
RUN apt-get update && apt-get -y install mlocate && updatedb

# download guatOJ 
WORKDIR /root/guatOJ/
RUN git clone https://github.com/jieshicheng/guatOJ.git

EXPOSE 80