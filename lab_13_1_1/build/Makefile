# Обычная сборка
all: test.exe

test.exe: test_wc.o wc.o
	gcc -Wall -Werror -o test.exe test_wc.o wc.o 

wc.o: ../wc/wc.c ../wc/wc.h
	gcc -Wall -Werror -c ../wc/wc.c

test_wc.o: ../tests/test_wc.c ../tests/test_wc.h ../wc/wc.h
	gcc -Wall -Werror -c ../tests/test_wc.c

# Сборка с использованием статической библиотеки
static: test_static.exe

test_static.exe: libwc.a ../tests/test_wc.c ../tests/test_wc.h
		gcc -Wall -Werror -o test_static.exe ../tests/test_wc.c -L. -lwc

libwc.a: ../wc/wc.c ../wc/wc.h
		gcc -Wall -Werror -c ../wc/wc.c
		ar rc libwc.a wc.o

# Сборка с динамической линковкой
dynamic_linkage: test_dyn_linkage.exe

libwc.so: ../wc/wc.c ../wc/wc.h
		gcc -Wall -Werror -c -fPIC ../wc/wc.c
		gcc -shared -Wall -Werror -o libwc.so wc.o

test_dyn_linkage.exe: libwc.so ../tests/test_wc.c ../tests/test_wc.h 
		gcc -Wall -Werror -c ../tests/test_wc.c
		export LD_LIBRARY_PATH='./'
		gcc -Wall -Werror -o test_dyn_linkage.exe test_wc.o -L. -lwc -Wl,-rpath,.

# Сборка с динамической загрузкой
dynamic_upload: test_dyn_upload.exe

test_dyn_upload.exe: libwc.so ../tests/test_wc_upload.c ../tests/test_wc_upload.h
		gcc -Wall -Werror -o test_dyn_upload.exe ../tests/test_wc_upload.c -ldl

# Создание динамической библитотеки dll
create_so: wc.so

wc.so: ../wc/wc.c ../wc/wc.h
		gcc $ -Wall -Werror -c -fPIC ../wc/wc.c
		gcc -shared -Wall -Werror -o wc.so wc.o

clean:
	rm *.o *.exe
