SOURCE1 := main
SOURCE2 := pthreads_funcs

all : result

result: $(SOURCE1).o $(SOURCE2).o
		gcc *.o -o result -g -pthread

$(SOURCE1).o: $(SOURCE1).c
		gcc $(SOURCE1).c -c	

$(SOURCE2).o: $(SOURCE2).c
		gcc $(SOURCE2).c -c
clean:
		rm result *.o
