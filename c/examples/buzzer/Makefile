# target: pre-req1 pre-req2
# Created with the help of https://earthly.dev/blog/g++-makefile/
target = buzzer # target executable
objects = buzzer.o

all: $(target)

buzzer: $(objects)
	g++ -Wall -o $(target) -lpigpio -lrt -lpthread $(objects)

buzzer.o: buzzer.cpp
	g++ -c buzzer.cpp

clean:
	rm *.o $(target)
