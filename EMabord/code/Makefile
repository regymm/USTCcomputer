all: simu

simu: simu.o
	$(CC) $^ -o $@
clean:
	-rm *.o simu
.PHONY: all, clean
CC = gcc
CFLAGS = -Wall -lm

