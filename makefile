CC=gcc
CFLAGS=-Wall
EXEC=main

all: $(EXEC)

main: main.o game.o
	$(CC) -o $@ $^ $(LDFLAGS)

game.o: displayprompt.h colour.h constants.h matrix.h types.h constants.h

displayprompt.o: colour.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)