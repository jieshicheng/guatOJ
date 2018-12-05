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

# install jdk
RUN apt-get -y install wget
WORKDIR /root/jdk
RUN wget --no-check-certificate --no-cookies --header "Cookie: oraclelicense=accept-securebackup-cookie" https://download.oracle.com/otn-pub/java/jdk/8u192-b12/750e1c8617c5452694857ad95c3ee230/jdk-8u192-linux-x64.tar.gz
RUN tar -zxvf /root/jdk/jdk-8u192-linux-x64.tar.gz -C /root/jdk/ && rm -rf /root/jdk/jdk-8u192-linux-x64.tar.gz

ENV JAVA_HOME /root/jdk/jdk1.8.0_192/
ENV PATH $PATH:$JAVA_HOME/bin

# download guatOJ 
WORKDIR /root/guatOJ/
RUN git clone https://github.com/jieshicheng/guatOJ.git

EXPOSE 8080