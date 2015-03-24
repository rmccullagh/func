objects = main.o
CCFLAGS = -Wall -Wextra -Wpedantic

main : $(objects)
		cc $(CCFLAGS) -o main $(objects)

.PHONY : clean
clean:
	rm -f main $(objects)
