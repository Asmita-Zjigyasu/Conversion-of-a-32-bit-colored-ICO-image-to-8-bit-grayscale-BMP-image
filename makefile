
output: main.o
	gcc main.o -o output

main.o: main.c structures.h
	gcc -c main.c

clean:
	rm *.o output