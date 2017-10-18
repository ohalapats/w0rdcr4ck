CMP=g++-7 -Wall --std=c++11

all: main.o
	$(CMP) main.o -o ws

main.o: word.cc
	$(CMP) -c word.cc -o main.o


clean:
	rm -f ./main.o
