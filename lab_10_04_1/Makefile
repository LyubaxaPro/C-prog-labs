app.exe: main.o cdio.o errors_processing.o program.o memory_functions.o check_functions.o compare_functions.o
	gcc -o app.exe main.o cdio.o errors_processing.o program.o memory_functions.o check_functions.o compare_functions.o -lm

test.exe: test.o cdio.o errors_processing.o program.o memory_functions.o compare_functions.o check_functions.o test_check_functions.o test_memory_functions.o test_compare_functions.o test_program.o
	gcc -o test.exe test.o cdio.o errors_processing.o program.o memory_functions.o compare_functions.o check_functions.o test_check_functions.o test_memory_functions.c test_compare_functions.o test_program.o -lm	

main.o: main.c cdio.h errors_processing.h structs.h program.h memory_functions.h compare_functions.h check_functions.h
	gcc -std=c99 -Wall -Werror -c main.c 

test.o: test.c cdio.h errors_processing.h structs.h program.h memory_functions.h compare_functions.h check_functions.h test_check_functions.h test_memory_functions.h
	gcc -std=c99 -Wall -Werror -c test.c 

program.o: program.c cdio.h errors_processing.h memory_functions.h compare_functions.h check_functions.h structs.h program.h
	gcc -std=c99 -Wall -Werror -c program.c 

cdio.o: cdio.c cdio.h errors_processing.h structs.h constants.h program.h memory_functions.h check_functions.h
	gcc -std=c99 -Wall -Werror -c cdio.c

errors_processing.o: errors_processing.c errors_processing.h constants.h
	gcc -std=c99 -Wall -Werror -c errors_processing.c

memory_functions.o: memory_functions.c memory_functions.h constants.h cdio.h errors_processing.h structs.h
	gcc -std=c99 -Wall -Werror -c memory_functions.c

check_functions.o: check_functions.c check_functions.h constants.h cdio.h errors_processing.h structs.h
	gcc -std=c99 -Wall -Werror -c check_functions.c

compare_functions.o: compare_functions.c compare_functions.h constants.h cdio.h errors_processing.h structs.h
	gcc -std=c99 -Wall -Werror -c compare_functions.c

test_check_functions.o: test_check_functions.c test_check_functions.h constants.h errors_processing.h structs.h check_functions.h
	gcc -std=c99 -Wall -Werror -c test_check_functions.c

test_memory_functions.o: test_memory_functions.c test_memory_functions.h constants.h cdio.h errors_processing.h structs.h check_functions.h
	gcc -std=c99 -Wall -Werror -c test_memory_functions.c

test_compare_functions.o: test_compare_functions.c test_compare_functions.h constants.h cdio.h errors_processing.h structs.h check_functions.h memory_functions.h
	gcc -std=c99 -Wall -Werror -c test_compare_functions.c

test_program.o: test_program.c test_compare_functions.h constants.h cdio.h errors_processing.h structs.h check_functions.h memory_functions.h program.h
	gcc -std=c99 -Wall -Werror -c test_program.c


clean:
	rm *.o *.exe
