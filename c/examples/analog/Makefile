# target: pre-req1 pre-req2
# Created with the help of https://earthly.dev/blog/g++-makefile/
target = analog # target executable
objects = mcp3008Spi.o analog.o

all: $(target)

analog: $(objects)
	g++ -Wall -o $(target) -lpigpio -lrt -lpthread $(objects)

mcp3008Spi.o: mcp3008Spi.cpp
	g++ -c mcp3008Spi.cpp

analog.o: analog.cpp
	g++ -c analog.cpp

clean:
	rm *.o $(target)
