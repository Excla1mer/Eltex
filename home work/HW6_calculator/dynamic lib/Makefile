

all: result

result: main.o libmy_lib.so
		gcc main.o -o result -L. -lmy_lib

main.o: main.c
		gcc main.c -c -g

libmy_lib.so: my_lib.o
		gcc -shared -o libmy_lib.so my_lib.o

my_lib.o: my_lib.c
		gcc -fPIC my_lib.c -c

run: result
		LD_LIBRARY_PATH="$(PWD)" ./result

clean:
		rm *.o *.so result
