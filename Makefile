
ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m   := hello.o
ccflags-y += -g
else
# normal makefile
KDIR := ~/repos/linux-stable

default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello.ko hello.ko.unstripped
	$(CROSS_COMPILE)strip --strip-debug hello.ko
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
	
%.s %.i: %.c # just use make hello.s instead of objdump
	$(MAKE) -C $(KDIR) M=$$PWD $@
    
endif
