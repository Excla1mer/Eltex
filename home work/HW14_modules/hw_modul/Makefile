obj-m += hw_modul.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	#make -C /usr/src/linux-5.4 SUBDIRS=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
