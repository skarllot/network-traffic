#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <time.h>

#include <dirent.h>

int main()
{
    time_t a_begin = time(NULL);
    for (int a = 0; a < 10000000; a++)
    {
        struct stat buf;
        int ret = stat("/home/fabricio", &buf);
        ret = stat("/home/nouser", &buf);
        //std::cout << a << std::endl;
    }
    time_t a_end = time(NULL);
    std::cout << "Test A took " << (a_end - a_begin) << " seconds" << std::endl;

    time_t b_begin = time(NULL);
    for (int b=0; b<10000000; b++)
    {
        DIR* dirp;
        dirp = opendir("/home/fabricio");
        dirp = opendir("/home/nouser");
        //std::cout << b << std::endl;
    }
    time_t b_end = time(NULL);
    std::cout << "Test B took " << (b_end - b_begin) << " seconds" << std::endl;

    return 0;
}
