## 1.cinatra

* boost.asio
* gcc7.2
* uuid

(ps: use correct ld and .so file)

## 2.jsoncpp

g++ test.cpp -o server -std=c++17 -luuid -lboost_system -lboost_filesystem -lpthread -lstdc++fs
