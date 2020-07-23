SOURCE1 := main
SOURCE2 := pthreads_funcs
SOURCE3 := pthreads_funcs_key

standart: result
key: result_key

result_key: $(SOURCE1).c $(SOURCE3).o
		gcc $(SOURCE1).c -c
		gcc *.o -o result_key -g -pthread
		rm *.o

result: $(SOURCE1).o $(SOURCE2).o
		gcc *.o -o result -g -pthread

$(SOURCE1).o: $(SOURCE1).c
		gcc $(SOURCE1).c -c -DSTANDART	

$(SOURCE2).o: $(SOURCE2).c
		gcc $(SOURCE2).c -c

$(SOURCE3).o: $(SOURCE3).c
		gcc $(SOURCE3).c -c


clean:
		rm result* *.o
