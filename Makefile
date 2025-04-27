obj-m += fanctrl.o

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(shell pwd) modules

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(shell pwd) clean

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(shell pwd) modules_install
