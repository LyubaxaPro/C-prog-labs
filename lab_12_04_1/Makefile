app.exe: main.o computation_functions.o base_functions.o
	gcc -o app.exe main.o computation_functions.o base_functions.o -lm

test.exe: test.o computation_functions.o base_functions.o test_base_functions.o test_computation_functions.o 
	gcc -o test.exe test.o computation_functions.o base_functions.o test_base_functions.o test_computation_functions.o -lm

test.o: test.c  structs.h base_functions.h computation_functions.h constants.h test_base_functions.h
	gcc -std=c99 -Wall -Werror -c test.c 

test_base_functions.o: test_base_functions.c  structs.h base_functions.h computation_functions.h constants.h test_base_functions.h
	gcc -std=c99 -Wall -Werror -c test_base_functions.c

test_computation_functions.o: test_computation_functions.c  structs.h base_functions.h computation_functions.h constants.h test_computation_functions.h
	gcc -std=c99 -Wall -Werror -c test_computation_functions.c

main.o: main.c  structs.h base_functions.h computation_functions.h constants.h
	gcc -std=c99 -Wall -Werror -c main.c 

computation_functions.o: computation_functions.c  structs.h base_functions.h computation_functions.h constants.h
	gcc -std=c99 -Wall -Werror -c computation_functions.c 

base_functions.o: base_functions.c  structs.h base_functions.h computation_functions.h constants.h
	gcc -std=c99 -Wall -Werror -c base_functions.c 

clean:
	rm *.o *.exe



