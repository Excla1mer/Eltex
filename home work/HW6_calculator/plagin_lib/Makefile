

all: result libsub.so libsum.so libdiv.so libmult.so 

libsub.so: sub.c
		gcc -fPIC sub.c -c
		gcc -shared -o libsub.so sub.o
libsum.so: sum.c
		gcc -fPIC sum.c -c -g
		gcc -shared -o libsum.so sum.o
libmult.so: mult.c
		gcc -fPIC mult.c -c
		gcc -shared -o libmult.so mult.o
libdiv.so: div.c
		gcc -fPIC div.c -c
		gcc -shared -o libdiv.so div.o
libdraw.a: draw.c
		gcc draw.c -c
		ar rc libdraw.a draw.o

result: main.c draw.c
		gcc main.c -c -g
		gcc draw.c -c -g
		gcc main.o draw.o -o result -ldl -Wl,-rpath,. 
clean:
		rm *.o result *.a *.so
