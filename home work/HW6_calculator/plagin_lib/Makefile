
SOURCE := sub.c sum.c div.c mult.c
libso := libsub.so libsum.so libdiv.so libmult.so
all: result $(libso) move 

$(libso): $(SOURCE)
		gcc -fPIC sub.c -c
		gcc -shared -o libsub.so sub.o
		gcc -fPIC sum.c -c -g
		gcc -shared -o libsum.so sum.o
		gcc -fPIC mult.c -c
		gcc -shared -o libmult.so mult.o	
		gcc -fPIC div.c -c
		gcc -shared -o libdiv.so div.o		

move: $(libso)	
	      	mv *.so plagins	

result: main.c draw.c
		gcc main.c -c -g
		gcc draw.c -c -g
		gcc main.o draw.o -o result -ldl -Wl,-rpath,./plagins/ 
clean:
		rm *.o result plagins/* 
