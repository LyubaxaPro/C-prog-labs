test.exe: test.o function.o
	gcc -o test.exe test.o function.o -lm

test.o: test.c test.h function.h
	gcc -std=c99 -Wall -c test.c

function.o: function.c test.h function.h
	gcc -std=c99 -Wall -Werror -c function.c