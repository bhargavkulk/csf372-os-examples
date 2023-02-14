#comments in makefiles!

CC:=gcc

# target : dependencies
# I only run the command if a dependency changes!
a.out: 4-main.o 4-sub.o 4-add.o
	$(CC) 4-main.o 4-sub.o 4-add.o

4-main.o: 4-main.c
	$(CC) -c 4-main.c -o 4-main.o

4-sub.o: 4-sub.c
	$(CC) -c 4-sub.c -o 4-sub.o

4-add.o: 4-add.c
	$(CC) -c 4-add.c -o 4-add.o

.PHONY: clean

clean:
	rm a.out *.o