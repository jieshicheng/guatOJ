#include <errno.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    rlimit *rlim = new rlimit;
    
    getrlimit(RLIMIT_AS, rlim);
    std::cout << rlim->rlim_cur << std::endl;
    
    // cpu time
    rlim->rlim_max = 10;
    rlim->rlim_cur = 10;
    setrlimit(RLIMIT_CPU, rlim);

    // memory size
    getrlimit(RLIMIT_DATA, rlim);
    
    rlim->rlim_max = 1024 * 1024 * 5;
    rlim->rlim_cur = 1024 * 1024 * 5;
    if (setrlimit(RLIMIT_RSS, rlim) == 0)
        std::cout << "yes" << std::endl;

    
    char *buf[50];

    for (int i = 0; i != 50; ++i)
    {
        buf[i] = (char *)calloc(1, 1024 * 1024 * 10);
        if (buf[i] == nullptr)
        {
            std::cout << errno << " ss " << ENOMEM << std::endl;    
        }
    }

    /*
    pid_t pid;
    if ((pid = fork()) == 0)
    {
        char *buf = (char *)malloc(1000 * 1024);
        if (buf == nullptr)
            std::cout << "null" << std::endl;
        memset(buf, 'a', 100 * 1024);
    }
    else
    {
        // wait
        int status;
        waitpid(pid, &status, 0);
        std::cout << "father process" << std::endl;
    }
    */
    //printf("%s", buf);
    //while (1);
    
    return 0;    
}
