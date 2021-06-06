CC=g++
CXXFLAGS=-Wall -g -std=c++11 -fno-stack-protector
SRCRESCH=src/resolveur
SRCGENCH=src/generateur
SRC=resolveur.cpp Situation.cpp Superviseur.cpp
OBJRES= obj/resolveur.o obj/Situation.o obj/Superviseur.o
OBJGEN= obj/generateur.o obj/Situation.o obj/Superviseur.o

all: resolveur generateur

bin/resolveur.ex: $(OBJRES)
	@$(CC) $(CXXFLAGS) $^ -o $@ -pthread & echo "Utilisation : bin/resolveur.ex [Chemin du puzzle à résoudre] (-t)" 

bin/generateur.ex: $(OBJGEN)
	@$(CC) $(CXXFLAGS) $^ -o $@ -pthread & echo "Utilisation : bin/generateur.ex [Nombre de coups minimal] (-t)"

obj/resolveur.o: $(SRCRESCH)/resolveur.cpp $(SRCRESCH)/Superviseur.h
	@$(CC) $(CXXFLAGS) -c $< -o $@

obj/Situation.o: $(SRCRESCH)/Situation.cpp $(SRCRESCH)/Situation.h
	@$(CC) $(CXXFLAGS) -c $< -o $@

obj/Superviseur.o: $(SRCRESCH)/Superviseur.cpp $(SRCRESCH)/Superviseur.h $(SRCRESCH)/Situation.h
	@$(CC) $(CXXFLAGS) -c $< -o $@

obj/generateur.o: $(SRCGENCH)/generateur.cpp $(SRCRESCH)/Superviseur.h $(SRCRESCH)/Superviseur.cpp
	@$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm obj/*.o

resolveur: bin/resolveur.ex

generateur: bin/generateur.ex
