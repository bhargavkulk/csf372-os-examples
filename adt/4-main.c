/*
We now have a new header file for the sub function. Any real code base would
so many more header files and implementation files.
Say we change soemthing in 4-sub.c.
We would have to run the command:
gcc 4-main.c 4-sub.c 4-add.c

We are compiling both 4-main.c and 4-add.c even though we didnt make any changes
in them! In a large codebase think about the compilation times! We can instead 
compile all of these c files into individual object files. We only compile the 
file that we changed, drastically reducing the compilation times of our project.

We do this by running:

gcc -c 4-main.c -o 4-main.o
gcc -c 4-add.c -o 4-add.o
gcc -c 4-sub.c -o 4-sub.o

gcc 4-main.o 4-add.o 4-sub.o

Now if we make a change to sub, we just do:
gcc -c 4-sub.c -o 4-sub.o
gcc 4-main.o 4-add.o 4-sub.o

We can automate this tedious process using makefiles!
*/

#include "4-sub.h"
#include "4-add.h"
#include <stdio.h>

int main() {
    printf("%d %d\n", add(1, 1), sub(1, 1));
}