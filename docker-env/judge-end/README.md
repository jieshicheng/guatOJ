## dockerfile && build:

```
docker build -t xxx/guatoj:v1 .
```

## run:

```
//You can use shell blow to build container.
docker run -d -p 80:8080 -it -v yourpath/guatOJ:/root/guatOJ/project xxx/guatoj:v1 /bin/bash
```