all: projet

projet: obj/main.o
	g++ -std=c++11 -o projet obj/main.o

obj/main.o: word2vec.h gestionfichier.h config.h decisions.h main.cpp 
	g++ -std=c++11 -o obj/main.o -c main.cpp 

clean:
	rm -f obj/*.o

clear: clean
	rm -f projet

re: clear all