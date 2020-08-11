SUS1 := server
SUS2 := client_udp
SUS3 := client_ip

all: $(SUS1) $(SUS2) $(SUS3)

ip: $(SUS1) $(SUS3)

udp: $(SUS1) $(SUS2)

$(SUS1): $(SUS1).c
		gcc $(SUS1).c -o $(SUS1) -g 

$(SUS2): $(SUS2).c
		gcc $(SUS2).c -o $(SUS2) -g

$(SUS3): $(SUS3).c
		gcc $(SUS3).c -o $(SUS3) -g

clear:
		rm $(SUS1) $(SUS2) $(SUS3)

