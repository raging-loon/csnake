all: main

CC=g++

main:
	$(CC) csnake.cpp snek.cpp GameData.cpp -o csnake -lcurses -ggdb