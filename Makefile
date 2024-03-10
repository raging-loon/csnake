all: main

CC=g++

main:
	$(CC) csnake.cpp snek.cpp Game.cpp -o csnake -lncursesw -ggdb