BIN1 := struct1
BIN2 := struct2

SOURCE1 := *1.c
SOURCE2 := *2.c

all: $(BIN1) $(BIN2)

$(BIN1): $(SOURCE1)
		gcc $(SOURCE1) -o $(BIN1) -g
$(BIN2): $(SOURCE2)
		gcc $(SOURCE2) -o $(BIN2) -g

clean:
		rm $(BIN1) $(BIN2)


