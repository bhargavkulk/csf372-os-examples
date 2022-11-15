#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char * argv[])
{
    //opening a preexisting file called testFile2.txt with read and write permissions
    int fd = open("testFile2.txt", O_RDWR);
    printf("The file descriptor is : %d\n", fd);
    //duplicating the file descriptor for it to a specific fd, namely 255
    int fd2 = dup2(fd, 255);
    printf("The new file descriptor is : %d\n", fd2);
    close(fd2);
    //duplicating again, but this time setting file descriptor 1 (by default, fd:1 points to STDOUT). Therefore now, any printfs will be written into testFile2.txt
    int std_out = dup2(fd, 1);
    close(fd);
    //this is written into testfile2
    printf("Hello, this is from dup2.c\n");

}
