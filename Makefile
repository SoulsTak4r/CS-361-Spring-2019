hw2.o: hw2.c
	gcc -c hw2.c

361shell: hw2.o hw2.h
	gcc -o 361shell hw2.o -lm

all: 361shell

clean:
	rm *.o 361shell

