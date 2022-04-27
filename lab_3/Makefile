CC_FLAGS := -I include

.PHONY: all clean

all: cfs

obj:
	mkdir obj


cfs: src/cfs.c include/heap.h | obj
	gcc $(CC_FLAGS) -o cfs  src/cfs.c  





clean: 
	rm -rf obj
