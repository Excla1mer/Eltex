BIN1 := struct1
BIN2 := struct2
SOURCE1 := struct1.c
SOURCE2 := struct2.c
all: $(BIN1) $(BIN2) struct2_1

$(BIN1): $(SOURCE1)
		gcc $(SOURCE1) -o $(BIN1) -g
$(BIN2): $(SOURCE2)
		gcc $(SOURCE2) -o $(BIN2) -g
struct2_1: struct2_1.c
		gcc struct2_1.c -o struct2_1 -g

clean:
		rm $(BIN1) $(BIN2) struct2_1


