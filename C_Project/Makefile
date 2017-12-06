all: GameofLife
GameofLife: GameofLife.o GoLui.o GoLvar.o
	$(CC) $^ -o $@
GameofLife.o: GoL.h
GoLui.c: GoL.h
GoLvar.c: GoL.h

clean:
	-rm *.o GameofLife

CFLAGS = -Wall
.PHONY: clean, all
