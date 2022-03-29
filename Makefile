CC=g++ -g -Wall

all: bin/main

bin/main : obj/main.o obj/game.o obj/monstre.o obj/defense.o obj/joueur.o obj/gameTxt.o
	$(CC) obj/main.o obj/game.o obj/monstre.o obj/defense.o obj/joueur.o obj/gameTxt.o obj/vecteur2D.o -o bin/test

obj/main.o : src/main.cpp
	$(CC) -c src/main.cpp -o obj/main.o

obj/game.o : src/game.cpp src/game.h obj/monstre.o obj/defense.o obj/joueur.o
	$(CC) -c src/game.cpp -o obj/game.o
	
obj/monstre.o : src/monstre.cpp src/monstre.h obj/vecteur2D.o
	$(CC) -c src/monstre.cpp -o obj/monstre.o

obj/defense.o : src/defense.cpp src/defense.h
	$(CC) -c src/defense.cpp -o obj/defense.o

obj/joueur.o : src/joueur.cpp src/joueur.h
	$(CC) -c src/joueur.cpp -o obj/joueur.o

obj/gameTxt.o : src/gameTxt.cpp src/gameTxt.h
	$(CC) -c src/gameTxt.cpp -o obj/gameTxt.o

obj/vecteur2D.o : src/vecteur2D.cpp src/vecteur2D.h
	$(CC) -c src/vecteur2D.cpp -o obj/vecteur2D.o

clean : 
	rm obj/*.o
	rm bin/*