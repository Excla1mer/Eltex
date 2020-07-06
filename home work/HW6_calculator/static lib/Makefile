

all: sub.o sum.o mult.o div.o draw.o
		ar rc libmy_lib.a *.o
		rm *.o
		gcc main.c -o test -L. -lmy_lib

sub.o: sub.c
		gcc sub.c -c -g
sum.o: sum.c
		gcc sum.c -c -g
mult.o: mult.c
		gcc mult.c -c -g
div.o: div.c
		gcc div.c -c -g
draw.o: draw.c
		gcc draw.c -c -g

clean:
		rm *.o test *.a
