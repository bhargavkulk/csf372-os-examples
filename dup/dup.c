#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
    //opening an existing file called testFile.txt
    int fd = open("testFile.txt", O_RDONLY);
    printf("The file descriptor is : %d\n", fd);
    //duplicating the file descriptor for said file. (dup provides the lowest available file descriptor)
    int fd2 = dup(fd);
    printf("The new file descriptor is : %d\n", fd2);
    close(fd);
    close(fd2);
}
