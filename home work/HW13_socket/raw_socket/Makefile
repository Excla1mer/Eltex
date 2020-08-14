SUS1 := server
SUS2 := client_udp
SUS3 := client_ip
SUS4 := client_eth

all: $(SUS1) $(SUS2) $(SUS3) $(SUS4)

ip: $(SUS1) $(SUS3)

udp: $(SUS1) $(SUS2)

eth: $(SUS1) $(SUS4)

$(SUS1): $(SUS1).c
		gcc $(SUS1).c -o $(SUS1) -g 

$(SUS2): $(SUS2).c
		gcc $(SUS2).c -o $(SUS2) -g

$(SUS3): $(SUS3).c
		gcc $(SUS3).c -o $(SUS3) -g

$(SUS4): $(SUS4).c
		gcc $(SUS4).c -o $(SUS4) -g


clear:
		rm $(SUS1) $(SUS2) $(SUS3) $(SUS4)

