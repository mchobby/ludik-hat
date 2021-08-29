# target: pre-req1 pre-req2
# Created with the help of https://earthly.dev/blog/g++-makefile/
target = joystick # target executable
objects = joy.o mcp3008Spi.o

all: $(target)

joystick: $(objects)
	g++ -Wall -o $(target) -lpigpio -lrt -lpthread $(objects)

joy.o: joy.cpp
	g++ -c joy.cpp

mcp3008Spi.o: mcp3008Spi.cpp
	g++ -c mcp3008Spi.cpp

clean:
	rm *.o $(target)
