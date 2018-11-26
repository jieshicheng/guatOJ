# guatOJ 服务器配置过程

## 服务器选择
服务器我选择的是腾讯云学生主机服务器。

配置：1核2G内存搭配50G硬盘。

不同的云服务器厂商有不同的配置过程这里就不一一详述了。

## 操作系统
操作系统采用的是CentOS 7 64位版本。

## 软件安装
* **Vim**

	```
	//首先安装vim
	yum install vim*
	//配置vim，以下内容为可选，主要是为了让vim更好用
	cd ~
	vi .vimrc
	//进入一个文本编辑窗口，按i键进入编辑，并输入一下内容
	set nocompatible
	syntax on
	set number
	set cursorline
	set ruler
	set shiftwidth=4
	set softtabstop=4
	set tabstop=4
	set nobackup
	set ignorecase smartcase
	set incsearch
	set hlsearch
	set showmatch
	set matchtime=2
	set guioptions-=T
	set guioptions-=m
	set smartindent
	//输入完成，按shift加：号，并输入wq保存退出。
	```
	
* **gcc/g++**:
	
	```
	yum install gcc
	yum install gcc-c++
	```
	
* **FTP**

	```
	//安装ftp服务器
	yum install vsftpd
	//设置开机启动ftp服务器
	chkconfig vsftpd on
	//开启ftp
	service vsftpd start
	//由于本服务器目前只对个人开放权限，用于个人转移文件
	//所以没用设置ftp用户以及各类登陆权限，有需求的可以自行发挥
	```
	
* **JDK**

	```
	//安装JDK，由于JDK官方需要点击接受才可开始下载所以使用wget不方便
	//这里我是去网站下载，然后通过FTP传到服务器上的
	//网址：http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html
	//选择dk-8u171-linux-x64.tar.gz，记得点击Accept圆点。
	//随后上传到服务器，然后解压
	tar -xvf jdk-8u171-linux-x64.tar.gz
	mkdir ~/jdk
	mv jdk1.8.0_171/ ~/jdk/
	//接下来配置JDK环境
	vim /etc/profile
	//进入编辑界面，按i进入编辑模式，拉到最下面，在后面追加以下数据
	//注意这里的所有路径都是因人所异的，例如我将jdk安装在root目录下
	//所以我的安装路径如下
	#JDK
	JAVA_HOME=/root/jdk/jdk1.8.0_171
	JRE_HOME=/root/jdk/jdk1.8.0_171/jre
	CLASS_PATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar:	$JRE_HOME/lib
	PATH=$PATH:$JAVA_HOME/bin:$JRE_HOME/bin
	export JAVA_HOME JRE_HOME CLASS_PATH PATH
	//按esc键，按：，输入wq保存并推出
	//使配置生效
	source /ect/profile
	//查看是否安装正确
	java -version
	//输出以下消息则安装成功
	//java version "1.8.0_171"
	//Java(TM) SE Runtime Environment (build 1.8.0_171-b11)
	//Java HotSpot(TM) 64-Bit Server VM (build 25.171-b11, mixed mode)
	```
	
* **Tomcat**

	```
	//安装tomcat
	wget http://mirrors.hust.edu.cn/apache/tomcat/tomcat-9/v9.0.8/bin/apache-tomcat-9.0.8.tar.gz
	//下载完成后进入到文件所在目录
	tar -xvf apache-tomcat-9.0.8.tar.gz
	mkdir ~/tomcat
	cp apache-tomcat-9.0.8 ~/tomcat/
	//启动tomcat
	～/tomcat/apache-tomcat-9.0.8/bin/startup.sh
	//用浏览器实验是否安装成功
	//你的服务器ip:8080
	//如果出现tomcat界面则代表安装成功
	```
	
* **Mysql**

	```
	//安装mysql源
	wget http://dev.mysql.com/get/mysql57-community-release-el7-8.noarch.rpm
	yum localinstall mysql57-community-release-el7-8.noarch.rpm
	yum install mysql-community-server
	//启动mysql
	systemctl start mysqld
	//设置开机启动
	systemctl enable mysqld
	systemctl daemon-reload
	//因为刚安装mysql会自动生成一个root密码，我们查看它
	grep 'temporary password' /var/log/mysqld.log
	//得到密码，可以登陆mysql了
	mysql -uroot -p
	//输入密码，进入mysql界面
	//修改root密码
	ALTER USER 'root'@'localhost' IDENTIFIED BY '你的密码'
	//注意这里密码需要大小写数字和符号。缺一个都不行。
	//修改mysql使用utf-8编码
	vim /etc/my.conf
	//找到[mysqld],在它后面追加以下内容
	character_set_server=utf8
	init_connect='SET NAMES utf8'
	//esc,: wq保存退出。重启mysql
	systemctl restart mysqld
	```
	