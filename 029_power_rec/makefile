CFLAGS=-std=gnu99 -pedantic -Wall
test: test-power.o power.o
	gcc -o test test-power.o power.o
test-power.o: test-power.c
	gcc $(CFLAGS) -c test-power.c
power.o: power.c
	gcc $(CFLAGS) -c power.c
