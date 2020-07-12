

all: result

result: main.c draw.c
		gcc main.c -c -g  
		gcc draw.c -c -g
		gcc main.o draw.o -o result -lncurses -g


clear:
		rm result *.o
