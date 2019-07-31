#makefile

all: main

Player.o: Player.cpp
	g++ -std=c++11 -c -g Player.cpp
	
Game.o: Game.cpp
	g++ -std=c++11 -c -g Game.cpp
	
main.o: main.cpp
	g++ -std=c++11 -c -g main.cpp
	
main: Player.o Game.o main.o
	g++ -o main main.o Game.o Player.o
	
clean: 
	rm *.o