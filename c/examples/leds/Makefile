# target: pre-req1 pre-req2
# Created with the help of https://earthly.dev/blog/g++-makefile/
target = leds # target executable
objects = leds.o

all: $(target)

leds: $(objects)
	g++ -Wall -o $(target) -lpigpio -lrt -lpthread $(objects)

leds.o: leds.cpp
	g++ -c leds.cpp

clean:
	rm *.o $(target)
