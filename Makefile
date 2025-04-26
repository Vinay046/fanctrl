obj-m += fanctrl.o

ccflags-y += -I$(src)

fanctrl-objs := fanctrl.o trace_fanctrl.o

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(shell pwd) modules

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(shell pwd) clean
