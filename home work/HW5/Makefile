BIN := test
SOURCE := test.c
BIN1  := gdb_test
file: $(BIN)
gdb: $(BIN1)
union: union
$(BIN): $(SOURCE)
		gcc $(SOURCE) -o $(BIN) -fno-stack-protector -g -DSAM
		./$(BIN) < file1.txt
		rm $(BIN)
$(BIN1): $(SOURCE)
		gcc $(SOURCE) -o $(BIN1) -fno-stack-protector -g -DGDB
		gdb ./$(BIN1)
		rm $(BIN1)
union: union.c
		gcc union.c -o union
		./union
		rm union
clear:
		rm $(BIN) $(BIN1)
