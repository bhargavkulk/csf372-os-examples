// assume that 3-add.c has a bajillion functions. We cant keep copy pasting
// function declarations again and again! Let's put all our declarations in a
// header file and "#include" it into our main file...

// This is called the interface file. 3-add.c will be our implementation file!

int add(int a, int b);