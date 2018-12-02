/**
 * This file tests how to using string as a buffer to store
 *  data which read from file 
 *
 * 2018-12-1: test successful, it work correctly.
 *  
 */


#include <iostream>
#include <unistd.h>
#include <string>
#include <memory>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main()
{
    string buffer;
    shared_ptr<char> sp(new char[512]);

    // open file
    int fd = open("../file.txt", O_RDONLY);    
    if (fd == -1)
    {
        cout << "fetal errno, can't open file.txt" << endl;
        exit(1);
    }

    size_t already_read = 0;
    int readed;
    while ((readed = read(fd, sp.get(), 512)) != 0)
    {
        if (readed == -1)
        {
            if (errno == EAGAIN)
            {
                break;
            }
            else
            {
                //fetal error
                cout << "fetal errno, read file return -1" << endl;
            }
        }
        sp.get()[readed] = '\0';
        already_read += readed;
        buffer += sp.get();
    }

    cout << buffer << endl;

    return 0;
}
