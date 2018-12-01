## 1.cinatra

* boost.asio
* gcc7.2
* uuid

(ps: use correct ld and .so file)

## 2.jsoncpp

## 3.docker use tips

```
// construct docker image
cd src/docker-env/compiler-env/ 
docker build -t jieshicheng/guatoj:v3 .

// run docker images
docker run -d -p 80:80 -it -v ~/Documents/GitHub/guatOJ/:/root/guatOJ/project jieshicheng/guatoj:v3 /bin/bash
```

