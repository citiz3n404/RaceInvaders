CC=gcc
CFLAGS=-Wall
SDLFLAG=-lSDL2
EXEC=main

all: $(EXEC)

main: main.o game.o displayprompt.o colour.o matrix.o
	$(CC) -o $@ $^ $(LDFLAGS) $(SDLFLAG)

main.o: game.h
game.o: displayprompt.h colour.h constants.h matrix.h types.h
displayprompt.o: colour.h
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
