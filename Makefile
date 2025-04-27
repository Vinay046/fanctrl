# Makefile for fanctrl module
obj-m += fanctrl.o

SRC := $(shell pwd)

# Add the current directory to include path for finding tracepoint headers
EXTRA_CFLAGS += -I$(SRC)

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) clean