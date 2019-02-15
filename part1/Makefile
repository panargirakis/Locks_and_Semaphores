all: part_1

part_1: part_1.o
	gcc -pthread part_1.o -o part_1 -lm

part_1.o: part_1.c
	gcc -g -c part_1.c

clean:
	rm -f *.o part_1

test: all
	./part_1 2 10 10 11 9 11 10
	echo test argument rejection
	./part_1 4 5 10 11 9 11 10
	./part_1 4 30 10 11 7 11 6
	echo ~~~~ cleaning ~~~~~
	make clean
