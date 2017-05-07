obj-m += module_helloworld.o
obj-m += module_proc_entry.o
obj-m += module_mmap.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
