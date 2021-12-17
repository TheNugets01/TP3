EXTFLAGS = -ansi -pedantic -Wall -std=c++11

all: sejours

MAP: EXTFLAGS += -DMAP
MAP: sejours

GETSET: EXTFLAGS += -DGETSET
GETSET: sejours

sejours : Catalogue.o ListeChainee.o Maillon.o Trajet.o  TrajetSimple.o TrajetCompose.o main.o 
		g++ -o sejours Catalogue.o ListeChainee.o Maillon.o Trajet.o TrajetSimple.o TrajetCompose.o main.o $(EXTFLAGS)

Catalogue.o : Catalogue.cpp
		g++ -c -g $(EXTFLAGS) Catalogue.cpp

ListeChainee.o : ListeChainee.cpp
		g++ -c -g $(EXTFLAGS) ListeChainee.cpp

Maillon.o : Maillon.cpp
		g++ -c -g $(EXTFLAGS) Maillon.cpp

Trajet.o : Trajet.cpp
		g++ -c -g $(EXTFLAGS) Trajet.cpp

TrajetSimple.o : TrajetSimple.cpp
		g++ -c -g $(EXTFLAGS) TrajetSimple.cpp

TrajetCompose.o : TrajetCompose.cpp
		g++ -c -g $(EXTFLAGS) TrajetCompose.cpp

main.o : main.cpp
		g++ -c -g $(EXTFLAGS) main.cpp
