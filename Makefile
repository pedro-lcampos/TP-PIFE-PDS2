CC := g++
FLAGS := -std=c++17 -Wall
TARGET := main.out

all: main

naipes:
	$(CC) $(FLAGS) -c naipes.cpp -o naipes.o

carta: naipes
	$(CC) $(FLAGS) -c carta.cpp -o carta.o

player: naipes carta
	$(CC) $(FLAGS) -c player.cpp -o player.o

pife: naipes carta player
	$(CC) $(FLAGS) -c pife.cpp -o pife.o

main: naipes carta player pife
	$(CC) $(FLAGS) player.o carta.o pife.o main.cpp -o $(TARGET)

clean:
	$(RM) -r *.o *.out $(TARGET)

tests: naipes carta player pife
	$(CC) $(FLAGS) naipes.o player.o carta.o pife.o unitTests/unit_tests.cpp -o unit_tests.out