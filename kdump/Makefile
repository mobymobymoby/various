KDIR = /lib/modules/$(shell uname -r)/build

obj-m := test.o

all : 
	$(MAKE) -C $(KDIR) M=$(PWD) modules;
	gcc -o app app.c;
	sudo insmod test.ko

clean : 
	$(MAKE) -C $(KDIR) M=$(PWD) clean;
	rm app;
	sudo rmmod test.ko
