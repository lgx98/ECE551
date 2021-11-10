test-bsearch: test-bsearch.cpp search.o
	g++ -g -std=gnu++98 -Wall -Werror -pedantic -o test test-bsearch.cpp search.o
search.o: search.cpp function.h
	g++ -c -g -std=gnu++98 -Wall -Werror -pedantic search.cpp
