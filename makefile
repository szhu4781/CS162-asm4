CC=g++ -g
EXE_FILE=hunt

all: $(EXE_FILE)

$(EXE_FILE): armor.o bats.o event.o game.o gold.o room.o stalactites.o wumpus.o main.o
	$(CC) armor.o bats.o event.o game.o gold.o room.o stalactites.o wumpus.o main.o -o $(EXE_FILE)

armor.o: armor.h armor.cpp
	$(CC) -c armor.cpp

bats.o: bats.h bats.cpp
	$(CC) -c bats.cpp

event.o: event.h event.cpp
	$(CC) -c event.cpp

game.o: game.h game.cpp
	$(CC) -c game.cpp 

gold.o: gold.h gold.cpp
	$(CC) -c gold.cpp

room.o: room.h room.cpp
	$(CC) -c room.cpp

stalactites.o: stalactites.h stalactites.cpp
	$(CC) -c stalactites.cpp

wumpus.o: wumpus.h wumpus.cpp
	$(CC) -c wumpus.cpp

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm -f *.o $(EXE_FILE)
