app.exe: main.o cdio.o errors_processing.o program.o
	gcc -o app.exe main.o cdio.o errors_processing.o program.o -lm

test.exe: test.o cdio.o errors_processing.o program.o
	gcc -o test.exe test.o cdio.o errors_processing.o program.o -lm

main.o: main.c cdio.h errors_processing.h structs.h program.h
	gcc -std=c99 -Wall -Werror -c main.c 

program.o: program.c cdio.h errors_processing.h structs.h program.h
	gcc -std=c99 -Wall -Werror -c program.c 

cdio.o: cdio.c cdio.h errors_processing.h structs.h constants.h
	gcc -std=c99 -Wall -Werror -c cdio.c

errors_processing.o: errors_processing.c errors_processing.h constants.h
	gcc -std=c99 -Wall -Werror -c errors_processing.c

clean:
	rm *.o *.exe