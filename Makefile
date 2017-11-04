CMP=g++-7 -Wall --std=c++11

all: main.o
	$(CMP) main.o -o ws

main.o: ws.cc data_horse.hpp
	$(CMP) -c ws.cc -o main.o


clean:
	rm -f ./main.o
