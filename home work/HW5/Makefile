BIN := test
SOURCE := *.c
BIN1  := gdb_test
all: $(BIN)
gdb: $(BIN1)
$(BIN): $(SOURCE)
		gcc $(SOURCE) -o $(BIN) -fno-stack-protector -g
		gdb ./$(BIN) < file.txt
		rm $(BIN)
$(BIN1): $(SOURCE)
		gcc $(SOURCE) -o $(BIN1) -fno-stack-protector -g
		gdb ./$(BIN1)
		rm $(BIN1)
clear:
		rm $(BIN) $(BIN1)
