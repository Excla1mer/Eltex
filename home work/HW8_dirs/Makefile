SOURCE := *.c
BIN := result

all: $(BIN)

$(BIN):  $(SOURCE)
		gcc $(SOURCE) -c 
	      	gcc *.o -o $(BIN) -g -lncurses -pthread
clear:
		rm $(BIN) *.o
		
