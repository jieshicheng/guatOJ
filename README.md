# guatOJ


***guatOJ*** 全称 ***桂林航天工业学院在线测评系统***，是一个面向互联网的在线算法测评网站，提供

* 算法题目在线浏览
* 在线提交代码测评

## 项目架构

***项目组成主要分为三个组件***

* 评测端使用C++ + Linux系统API
    * 本身是一个微型http服务器，提供restful接口供外部调用
* 网站后端使用PHP + nginx
    * 网站本身完成用户相关操作与存储
    * 需要评测代码，调用评测端API
* Linux客户端，采用命令行式交互方式，直接与评测端交互

其中每个组件互相独立，互相运行在各自提供的接口层次上

## Docker结构

***项目由三个docker镜像组成***

* 评测端（C++）Dockerfile : docker-env/judge-end/
* 网站后端（PHP + nginx）Dockerfile : docker-env/web-end/
* 数据库端（Mysql）Dockerfile : docker-env/mysql

## 安装说明

待完成

## 使用介绍

待完成

