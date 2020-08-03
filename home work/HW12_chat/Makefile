SUS1 := server
SUS2 := client

all: $(SUS1) $(SUS2)


$(SUS1): $(SUS1).c
		gcc $(SUS1).c -o $(SUS1) -lrt -g -pthread

$(SUS2): $(SUS2).c
		gcc $(SUS2).c -o $(SUS2) -lrt -g -pthread -lncurses

clear:
		rm $(SUS1) $(SUS2)

