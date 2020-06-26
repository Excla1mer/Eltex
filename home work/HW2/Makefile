BIN1 := arrays1
BIN2 := arrays2
BIN3 := arrays3
BIN4 := arrays4
SOURCE1 := *1.c
SOURCE2 := *2.c
SOURCE3 := *3.c
SOURCE4 := *4.c


all: $(BIN1) $(BIN2) $(BIN3) $(BIN4)

$(BIN1): $(SOURCE1)
		gcc $(SOURCE1) -o $(BIN1)

$(BIN2): $(SOURCE2)
		gcc $(SOURCE2) -o $(BIN2)

$(BIN3): $(SOURCE3)
		gcc $(SOURCE3) -o $(BIN3)

$(BIN4): $(SOURCE4)
		gcc $(SOURCE4) -o $(BIN4)

clean:
		rm $(BIN1) $(BIN2) $(BIN3) $(BIN4)


