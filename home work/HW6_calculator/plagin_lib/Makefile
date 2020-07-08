

all: libsub.so libsum.so libmult.so libdiv.so libdraw.a 

libsub.so: sub.c
		gcc -fPIC sub.c -c
		gcc -shared -o libsub.so sub.o
libsum.so: sum.c
		gcc -fPIC sum.c -c
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

result: main.c libdraw.a
		gcc main.c -o result -L. -ldraw
clean:
		rm *.o result *.a *.so
