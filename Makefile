all: part_1

part_1: part_1.o
	gcc -pthread part_1.o -o part_1 -lm

part_1.o: part_1.c
	gcc -g -c part_1.c

clean:
	rm -f *.o part_1