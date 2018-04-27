all: projet

projet: obj/main.o
	g++ -std=c++11 -o projet obj/main.o

obj/main.o: src/word2vec.h src/gestionfichier.h src/config.h src/decisions.h main.cpp 
	g++ -std=c++11 -o obj/main.o -c main.cpp -W -Wall -ansi 

clean:
	rm -f obj/*.o

clear: clean
	rm -f projet

re: clear all