SDL2=`sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
CC=g++ -g -Wall

all: bin/main

bin/main : obj/main.o obj/game.o obj/monstre.o obj/defense.o obj/joueur.o obj/gameTxt.o obj/gameGraphique.o obj/vecteur2D.o obj/Image.o
	$(CC) obj/main.o obj/game.o obj/monstre.o obj/defense.o obj/joueur.o obj/gameTxt.o obj/gameGraphique.o obj/vecteur2D.o obj/Image.o -o bin/test $(SDL2)

obj/main.o : src/main.cpp
	$(CC) -c src/main.cpp -o obj/main.o $(SDL2)

obj/game.o : src/game.cpp src/game.h obj/monstre.o obj/defense.o obj/joueur.o
	$(CC) -c src/game.cpp -o obj/game.o $(SDL2)
	
obj/monstre.o : src/monstre.cpp src/monstre.h obj/vecteur2D.o
	$(CC) -c src/monstre.cpp -o obj/monstre.o $(SDL2)

obj/defense.o : src/defense.cpp src/defense.h
	$(CC) -c src/defense.cpp -o obj/defense.o $(SDL2)

obj/joueur.o : src/joueur.cpp src/joueur.h
	$(CC) -c src/joueur.cpp -o obj/joueur.o $(SDL2)

obj/gameTxt.o : src/gameTxt.cpp src/gameTxt.h
	$(CC) -c src/gameTxt.cpp -o obj/gameTxt.o $(SDL2)

obj/gameGraphique.o : src/gameGraphique.cpp src/gameGraphique.h
	$(CC) -c src/gameGraphique.cpp -o obj/gameGraphique.o $(SDL2)

obj/vecteur2D.o : src/vecteur2D.cpp src/vecteur2D.h
	$(CC) -c src/vecteur2D.cpp -o obj/vecteur2D.o $(SDL2)

obj/Image.o : src/Image.cpp src/Image.h
	$(CC) -c src/Image.cpp -o obj/Image.o $(SDL2)

clean : 
	rm obj/*.o
	rm bin/*
