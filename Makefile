CMP=g++-7 -Wall --std=c++11

all: main.o args.o
	$(CMP) main.o args.o -o ws

main.o: ws.cc data_horse.hpp args.hpp
	$(CMP) -c ws.cc -o main.o

args.o: args.cc args.hpp
	$(CMP) -c args.cc -o args.o


clean:
	rm -f ./main.o
	rm -f ./args.o
