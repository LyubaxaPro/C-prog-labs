app.exe: main.o CDIO.o program.o errors_processing.o
	gcc -o app.exe main.o CDIO.o program.o errors_processing.o

test.exe: test.o CDIO.o program.o errors_processing.o
	gcc -o test.exe test.o CDIO.o program.o errors_processing.o

test.o:test.c CDIO.h constants.h program.h errors_processing.h
	gcc -std=c99 -Wall -Werror -c test.c

main.o: main.c CDIO.h program.h errors_processing.h
	gcc -std=c99 -Wall -Werror -c main.c 

CDIO.o: CDIO.c CDIO.h program.h errors_processing.h
	gcc -std=c99 -Wall -Werror -c CDIO.c

program.o: program.c program.h CDIO.h errors_processing.h
	gcc -std=c99 -Wall -Werror -c program.c

errors_processing.o: errors_processing.c errors_processing.h constants.h
	gcc -std=c99 -Wall -Werror -c errors_processing.c

clean:
	rm *.o *.exe