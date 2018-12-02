## dockerfile && build:

This is mysql:5's dockerfile. you can use 

```
docker pull mysql:5
// or
docker build -t xxxx/mysql:5 .
```

## run:

```
//run shell blow:
docker run --name mysql -p 12345:3306 -e MYSQL_ROOT_PASSWORD=yourpasswd -d mysql:5
```