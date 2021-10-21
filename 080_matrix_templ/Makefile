CCFLAGS=--std=gnu++11 -pedantic -Wall -Werror -ggdb3
matrixTest:  test.o
	g++ -o matrixTest $(CCFLAGS) test.o

%.o: %.cpp Matrix.h
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ matrixTest
