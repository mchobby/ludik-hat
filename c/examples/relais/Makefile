# target: pre-req1 pre-req2
# Created with the help of https://earthly.dev/blog/g++-makefile/
target = relais # target executable
objects = relais.o

all: $(target)

relais: $(objects)
	g++ -Wall -o $(target) -lpigpio -lrt -lpthread $(objects)

relais.o: relais.cpp
	g++ -c relais.cpp

clean:
	rm *.o $(target)
