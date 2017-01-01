FILES = game.c player.c deck.c studPokerRules.c studPokerUnitTest.c
OBJ = game.o player.o deck.o studPokerRules.o studPokerUnitTest.o
CC = gcc
OUT_EXEC = cardGame.out

build:$(OBJ)
	$(CC) $(FILES) -o $(OUT_EXEC)

clean:	
	rm -f *.o

rebuild: clean	build