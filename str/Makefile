CCFLAGS = -g -Wall -Wextra -Wpadded

default: size.o
	gcc $(CCFLAGS) -o size size.o
size.o: size.c
	gcc $(CCFLAGS) -c size.c
clean:
	rm -f *.o *.exe size
