CC=g++ -g -Wall

all: bin/test

bin/test : obj/main.o obj/game.o
	$(CC) obj/main.o obj/game.o -o bin/test

obj/main.o : src/main.cpp src/game.h
	$(CC) -c src/main.cpp -o obj/main.o

obj/game.o : src/game.cpp src/game.h
	$(CC) -c src/game.cpp -o obj/game.o

obj/monstre.o : src/monstre.cpp src/monstre.h
	$(CC) -c src/monstre.cpp -o obj/monstre.o

obj/defense.o : src/defense.cpp src/defense.h
	$(CC) -c src/defense.cpp -o obj/defense.o

obj/Joueur.o : src/Joueur.cpp src/Joueur.h
	$(CC) -c src/Joueur.cpp -o obj/Joueur.o

clean : 
	rm obj/*.o