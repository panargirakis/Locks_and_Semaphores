all: part_2

part_2: part_2.o
	gcc -pthread part_2.o -o part_2 -lm

part_2.o: part_2.c
	gcc -g -c part_2.c

clean:
	rm -f *.o part_2
