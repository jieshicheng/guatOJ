## 1.cinatra

* boost.asio
* gcc7.2
* uuid

(ps: use correct ld and .so file)

g++ test.cpp -o server -std=c++17 -luuid -lboost_system -lboost_filesystem -lpthread -lstdc++fs

## 2.jsoncpp