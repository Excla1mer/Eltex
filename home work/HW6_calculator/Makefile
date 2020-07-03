

all: main.o sub.o sum.o mult.o div.o draw.o
		gcc *.o -o result
		rm *.o
main.o: main.c
		gcc main.c -c -g
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
		rm *.o result
