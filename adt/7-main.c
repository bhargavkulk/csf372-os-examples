#include <stdio.h>

// How do I know which header file a function is in? Use man!
#include <stdlib.h>

int main() {
    // This array is allocated on the stack. It has a fixed size; we cant move
    // more than 1024 ints.
    int array[1024];

    // But the world is dynamic! We may need more than 1024 ints. So we can ask
    // the OS to allocate memory for us on the heap.

    /*
    void *malloc(size_t size)
    malloc allocates a size number of bytes and returns a pointer to the
    allocated memory.

    What is void *?
    void is nothing and void * is everything!
    A pointer to void is a "generic" pointer type. You cannot dereference a void * or do pointer arithmetic with it; you must convert it to a pointer to a complete data type first.

    As we should be able dynamically allocate memory for any type, malloc
    returns a void *, allowing us to just cast it into the type we need to use
    it for.
    */
    int *dyn_array = (int *)malloc(1024 * sizeof(int));

    /*
    But what happens if we dont have 1024 contiguous memory locations? Then
    the OS cannot allocate memory for us. malloc in that case returns NULL. This
    is the return value on error. So we should check for that.
    */
    if(dyn_array == NULL) {
        // prints the error
        // C library functions set a global error variable.
        // looking at the variable, perror prints a error message
        perror("malloc");
        exit(1);
    }

    /*
    Now we have 1024 ints, what if we want to double that? We can ask the OS
    to reallocate memory for us:

    void *realloc(void *ptr, size_t size);
    The realloc() function changes the size of the memory block pointed to by 
    ptr to size bytes.  The contents will be unchanged in the range from the 
    start of the region up to the minimum  of  the old and new sizes. If the 
    new size is larger than the old size, the added memory will not be 
    initialized.
    */

    int *new_mem = (int *)realloc(dyn_array, sizeof(int) * 2048);
    // We now check for error
    if(new_mem == NULL) {
        perror("realloc");
        exit(1);
    } else {
        dyn_array = new_mem;
    }

    /*
    Now we are done with our dyn_array. As a responsible programmer we should
    return back all the memory that the OS gave us:

    void free(void *ptr):
    The free() function frees the memory space pointed to by ptr, which must have been returned by a previous call to malloc() or realloc().  Otherwise, If free(ptr) has already been called before, undefined behavior occurs.
    The behaviour is usually an double free error.
    */

    free(dyn_array);
}